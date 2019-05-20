#ifndef PROCESS_CONTAINER_H
#define PROCESS_CONTAINER_H

#include <vector>

#include "Process.h"

using std::string;
using std::to_string;

class ProcessContainer
{
    private:
        vector<Process>_list;
    public:
        ProcessContainer() { this->refreshList(); }
        void refreshList();
        string printList();
        vector<vector<string>> getList();
};

#endif // PROCESS_CONTAINER_H