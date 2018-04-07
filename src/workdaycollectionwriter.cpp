#include "workdaycollectionwriter.h"
#include "libs/pugixml/pugixml.hpp"

WorkDayCollectionWriter::WorkDayCollectionWriter(std::vector<WorkDay> workDayCollection):
    _workDays   (workDayCollection)
{

}

WorkDayCollectionWriter::~WorkDayCollectionWriter()
{

}

void WorkDayCollectionWriter::write(std::string filename) const
{

}

std::string WorkDayCollectionWriter::writeToString() const
{
    return "";
}

