#pragma once

class PrintJob
{
public:
    PrintJob();

    void create(int copies);

    bool hasJob() const;
    int getTotalCopies() const;
    int getRemainingCopies() const;

    bool printOne();

    void clear();

private:
    int totalCopies;
    int remainingCopies;
};