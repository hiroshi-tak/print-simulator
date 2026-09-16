# Printer Simulator

C++で作成した、架空の産業用プリンターを想定したシミュレータです。

簡単なプリンター制御システムとして実装しています。

> 本プロジェクトは実際のプリンター製品の内部仕様を再現したものではありません。

---

## 概要

プリンターの基本的な状態管理に加えて、モーター、用紙センサー、印刷方式を組み合わせて動作する構成としています。

印刷方式については、

* インクジェット方式
* レーザー方式

の2種類を用意し、共通インターフェースを利用して切り替えられる構造としています。

---



## システム構成

```text
                    PrinterDevice
                 （印刷方式の共通IF）
                         ▲
                ┌────────┴────────┐
                │                 │
          InkjetPrinter      LaserPrinter
                │                 │
                └────────┬────────┘
                         │
                      Printer
                   （プリンター制御）
                    /          \
                   /            \
                Motor          Sensor
              （モーター）     （用紙センサー）
```

### Printer

プリンター全体の制御を担当します。

主な機能：

* 印刷開始
* 印刷停止
* 印刷完了
* プリンター状態管理
* モーター制御
* 用紙センサー確認
* 印刷方式への印刷指示

### Motor

プリンター内部のモーターを簡易的にモデル化しています。

```cpp
start()
stop()
isRunning()
```

### Sensor

用紙の検出状態を管理します。

```cpp
setPaperDetected()
isPaperDetected()
```

用紙が検出されていない場合、印刷を開始しないようにしています。

### PrinterDevice

印刷方式の共通インターフェースです。

```cpp
virtual void print() = 0;
virtual void print(int copies) = 0;
```

### InkjetPrinter

`PrinterDevice`を継承したインクジェット方式のプリンターです。

### LaserPrinter

`PrinterDevice`を継承したレーザー方式のプリンターです。

---

## C++の学習ポイント

### 1. 継承

```cpp
class InkjetPrinter : public PrinterDevice
{
};
```

`InkjetPrinter`と`LaserPrinter`は、共通の`PrinterDevice`を継承しています。

---

### 2. 純粋仮想関数

```cpp
virtual void print() = 0;
```

`PrinterDevice`では具体的な印刷処理を実装せず、派生クラスで実装する構成としています。

---

### 3. オーバーライド

```cpp
void print() override;
```

派生クラスで、基底クラスの仮想関数を具体的に実装しています。

---

### 4. オーバーロード

```cpp
void print();
void print(int copies);
```

同じ`print`という関数名で、引数の異なる関数を用意しています。

例えば、

```cpp
printer.print();
```

と

```cpp
printer.print(3);
```

のように呼び出せます。

---

### 5. ポリモーフィズム

```cpp
PrinterDevice* device = &inkjet;
device->print();
```

`PrinterDevice*`という共通の型を使用しながら、実際のオブジェクトに応じて`InkjetPrinter::print()`や`LaserPrinter::print()`が呼び出されます。

これにより、印刷方式の違いを意識せずに共通のインターフェースから処理できます。

---

## プリンターの状態

プリンターの状態は`PrinterState`で管理しています。

```cpp
enum class PrinterState
{
    IDLE,
    PRINTING,
    STOPPED
};
```

状態遷移のイメージ：

```text
             startPrint()
       ┌────────────────────┐
       │                    ▼
     IDLE ─────────────> PRINTING
       ▲                    │
       │                    │ stopPrint()
       │                    ▼
       │                 STOPPED
       │                    │
       └────────────────────┘
             startPrint()

PRINTING
    │
    │ finishPrint()
    ▼
  IDLE
```

---

## 印刷開始処理

印刷開始時には、以下の順番で処理します。

```text
startPrint()
     │
     ▼
プリンター状態を確認
     │
     ▼
用紙センサーを確認
     │
     ├── 用紙なし → 印刷開始しない
     │
     ▼
モーター開始
     │
     ▼
状態をPRINTINGへ変更
     │
     ▼
PrinterDevice::print()
```

---

## ディレクトリ構成

```text
printer-simulator/
├── src/
│   ├── main.cpp
│   │
│   ├── printer/
│   │   ├── Printer.h
│   │   ├── Printer.cpp
│   │   └── PrinterState.h
│   │
│   ├── device/
│   │   ├── PrinterDevice.h
│   │   ├── PrinterDevice.cpp
│   │   ├── InkjetPrinter.h
│   │   ├── InkjetPrinter.cpp
│   │   ├── LaserPrinter.h
│   │   └── LaserPrinter.cpp
│   │
│   └── hardware/
│       ├── Motor.h
│       ├── Motor.cpp
│       ├── Sensor.h
│       └── Sensor.cpp
│
├── docs/
│   └── uml/
│       ├── class.puml
│       ├── sequence.puml
│       └── state.puml
│
└── README.md
```


## ビルド方法

Ubuntu / WSL環境で以下を実行します。

```bash
cd ~/printer-simulator
```

コンパイル：

```bash
g++ -std=c++17 \
    -Isrc \
    src/main.cpp \
    src/printer/Printer.cpp \
    src/device/PrinterDevice.cpp \
    src/device/InkjetPrinter.cpp \
    src/device/LaserPrinter.cpp \
    src/hardware/Motor.cpp \
    src/hardware/Sensor.cpp \
    -o build/printer
```

実行：

```bash
./build/printer
```

---

## 実行例

```text
=== インクジェットプリンター ===
初期状態: IDLE
インクジェット方式で1部印刷します
印刷状態: PRINTING
モーター: 1
印刷完了後: IDLE

=== レーザープリンター ===
レーザー方式で1部印刷します
印刷状態: PRINTING
モーター: 1
印刷完了後: IDLE
```

---

## UML

設計内容はPlantUMLを使用してドキュメント化しています。

主なUML：

* クラス図
* シーケンス図
* 状態遷移図

UMLファイル：

```text
docs/uml/
```

---

## 使用技術

| 項目      | 内容                 |
| ------- | ------------------ |
| 言語      | C++                |
| C++規格   | C++17              |
| ビルド     | g++                |
| 開発環境    | Ubuntu / WSL       |
| エディタ    | Visual Studio Code |
| 設計      | UML / PlantUML     |
| バージョン管理 | Git / GitHub       |

---

## 今後の改善候補

以下を検討します。

* エラー状態の追加
* 紙詰まり検出
* インク・トナー残量管理
* 印刷ジョブ管理
* タイマーによる状態遷移
* ログ出力
* CMakeによるビルド環境整備
* 単体テスト

---

