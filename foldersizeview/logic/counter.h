#ifndef COUNTER_H
#define COUNTER_H


#include <QDebug>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDateTime>
#include <stack>
#include <list>
#include <map>


/**
 * @brief The Counter class
 *
 * DirectoryCount
 *
 * FileCount
 * FileCount 0-1MB 1-10MB 10-xMB
 * Top 10 Large File
 * Top 10 Small File
 *
 * FileTypeCount
 * <FileType,TotalSize>
 * <FileType,Count>
 *
 */
class Counter
{
public:
    Counter();


    void countFileInfo(const QFileInfo & info);

public:
    int mDirectoryCount = 0;
    int mFileCount = 0;

    int mFileCount0_1MB = 0;
    int mFileCount1_10MB = 0;
    int mFileCount10_XMB = 0;

    std::list<QFileInfo> mTop10LargeFile;
    std::list<QFileInfo> mTop10SmallFile;

    std::map<QString,int64_t> mFileTypeTotalSizeMap;
    std::map<QString,int> mFileTypeCountMap;


};

#endif // COUNTER_H
