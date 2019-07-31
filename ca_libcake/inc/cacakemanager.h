//
// Created by angelo on 19/06/19.
//

#ifndef QXMLC_CACAKEMANAGER_H
#define QXMLC_CACAKEMANAGER_H




#include "cainterfaces.h"
#include "caminiXml.h"
#include "calcfxml.h"
#include "camainconf.h"
#include "cajobstep.h"

namespace CA
{




class cakeManager
    : public CA::ICake
{
private :
    CAXml_Main conf;
    IGetConfEnv  *env;
    std::vector<ICAjob_step *> jobs;
    void prepareDefaultEnv(void);
public:
    cakeManager();
    ~cakeManager();
    bool run (const std::string & conf_file ) final;
    void reset () final;
};

}
#endif //QXMLC_CACAKEMANAGER_H
