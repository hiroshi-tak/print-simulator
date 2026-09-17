#include "PrintJob.h"

PrintJob::PrintJob()
{
    this->totalCopies = 0;
    this->remainingCopies = 0;
}

void PrintJob::create(int copies)
{
    if (copies <= 0)
    {
        return;
    }

    this->totalCopies = copies;
    this->remainingCopies = copies;
}

bool PrintJob::hasJob() const
{
    return this->remainingCopies > 0;
}

int PrintJob::getTotalCopies() const
{
    return this->totalCopies;
}

int PrintJob::getRemainingCopies() const
{
    return this->remainingCopies;
}

bool PrintJob::printOne()
{
    if (this->remainingCopies <= 0)
    {
        return false;
    }

    this->remainingCopies--;

    return true;
}

void PrintJob::clear()
{
    this->totalCopies = 0;
    this->remainingCopies = 0;
}