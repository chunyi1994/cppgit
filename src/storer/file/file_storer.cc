#include "file_storer.h"

namespace git {

FileStorer *FileStorer::New(std::string path)
{

}

FileStorer::FileStorer(std::string path):
    path_(std::move(path))
{

}

} //namespace
