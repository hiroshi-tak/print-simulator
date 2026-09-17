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

また、紙詰まりを別スレッドから発生させ、センサーからの異常信号をPrinterが検出してエラー処理を行う構成としています。

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
                         │ 
        ┌────────────────┼────────────────┐ 
        │                │                │ 
        Motor         Sensor            Timer 
     （モーター）    （用紙センサー）    （タイマー）
                         │
                      mutex
                    （排他制御） 
                        │
                      PrintJob 
                    （印刷ジョブ）


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
* 紙詰まり検出
* 印刷ジョブ管理
* 印刷方式への印刷指示
* エラー検出・復旧
* タイマー制御

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

setPaperJamDetected()
isPaperJamDetected()
```

用紙が検出されていない場合、印刷を開始しないようにしています。
紙詰まり状態は別スレッドから設定され、Printer側で検出します。
また、複数スレッドからSensorへアクセスするため、std::mutexによる排他制御を行っています。

### Timer

印刷処理の時間経過を簡易的にシミュレーションします。

```cpp
start()
stop()
tick()
isExpired()
```

実際の時間を直接管理するのではなく、tick()を呼び出すことで時間経過をシミュレーションしています。

### PrintJob

印刷ジョブの部数を管理します。

```cpp
create()
hasJob()
getTotalCopies()
getRemainingCopies()
printOne()
clear()
```

総部数と残り部数を管理し、1部印刷するごとに残り部数を減らします。

### PrinterDevice

印刷方式の共通インターフェースです。

```cpp
virtual void print() = 0; 
virtual void print(int copies) = 0; 
virtual int getRemainingAmount() const = 0; 
virtual void consumeAmount(int amount) = 0;
```

### InkjetPrinter

`PrinterDevice`を継承したインクジェット方式のプリンターです。

### LaserPrinter

`PrinterDevice`を継承したレーザー方式のプリンターです。

### Logger

システムの状態や異常をログとして出力します。

```cpp
Logger::info()
Logger::warning()
Logger::error()
```

ログレベルとして、INFO、WARNING、ERRORを使用しています。

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


### 6. マルチスレッド

紙詰まりを別スレッドから発生させています。

```cpp
std::thread jamThread(
    paperJamInterrupt,
    std::ref(printer));
```

印刷処理とは独立したスレッドから紙詰まり信号を発生させることで、非同期に異常が発生する状況をシミュレーションしています。

### 7. mutexによる排他制御

メインスレッドと紙詰まりスレッドからSensorへアクセスするため、std::mutexによる排他制御を行っています。

```cpp
std::lock_guard<std::mutex> lock(this->mutex);
```

Sensorの状態を読み書きする処理をmutexで保護しています。
---

## プリンターの状態

プリンターの状態は`PrinterState`で管理しています。

```cpp
enum class PrinterState
{
    IDLE,
    PRINTING,
    STOPPED,
    ERROR
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

PRINTING
　　│
　　│ 紙詰まり検出 
　　▼
　ERROR
　　│ 
　　│ clearError() 
　　▼ 
　IDLE

```
---

## エラー処理

現在、以下のエラーを定義しています。
```cpp
enum class PrinterError
{
    NONE,
    PAPER_JAM,
    NO_PAPER,
    INK_EMPTY
};
```

紙詰まり発生時は、別スレッドからSensorへ紙詰まり信号を設定します。

```text
紙詰まり割り込み
       │
       ▼
     Sensor
       │
       │ 紙詰まり状態
       ▼
    Printer
       │
       ▼
     ERROR
       │
       │ エラー復旧
       ▼
      IDLE
       │
       │ 印刷再開
       ▼
   PRINTING

エラー発生時にはモーターを停止し、エラー解除後に印刷を再開します。

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
     
```
---
## ログ出力

Loggerクラスを使用してログを出力します。

```text
[INFO]
[WARNING]
[ERROR]

実行例：

[INFO] 印刷を開始します
[WARNING] 紙詰まり割り込み発生

=== エラー検出 ===
エラー: PAPER_JAM

=== エラー復旧 ===
[INFO] エラーから復旧しました
[INFO] 印刷を開始します
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
│   │   ├── PrinterError.h
│   │   ├── PrintJob.h
│   │   └── PrintJob.cpp
│   │
│   ├── device/
│   │   ├── PrinterDevice.h
│   │   ├── PrinterDevice.cpp
│   │   ├── InkjetPrinter.h
│   │   ├── InkjetPrinter.cpp
│   │   ├── LaserPrinter.h
│   │   └── LaserPrinter.cpp
│   │
│   ├── hardware/
│   │   ├── Motor.h
│   │   ├── Motor.cpp
│   │   ├── Sensor.h
│   │   ├── Sensor.cpp
│   │   ├── Timer.h
│   │   └── Timer.cpp
│   │
│   └── logger/
│       ├── Logger.h
│       └── Logger.cpp
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
rm -rf build/*
cmake -S . -B build
cmake --build build
```

実行：

```bash
./build/printer
```

---

## 実行例

```text
=== 初期状態 ===
状態: IDLE
残量: 100

=== 印刷ジョブ登録 ===
総部数: 5
残り部数: 5

=== 印刷開始 ===
[INFO] 印刷を開始します
状態: PRINTING
モーター: 1

インクジェット方式で印刷します
1秒経過
残り部数: 4
残量: 99

インクジェット方式で印刷します
1秒経過
残り部数: 3
残量: 98

[WARNING] 紙詰まり割り込み発生

=== エラー検出 ===
エラー: PAPER_JAM

=== エラー復旧 ===
[INFO] エラーから復旧しました
[INFO] 印刷を開始します

インクジェット方式で印刷します
1秒経過
残り部数: 2
残量: 97

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



