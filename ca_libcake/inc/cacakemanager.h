//
// Created by angelo on 19/06/19.
//

#ifndef CA_CAKE_MANAGER_H
#define CA_CAKE_MANAGER_H




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
    caJobStepManager jobs;
    void prepareDefaultEnv(void);
public:
    cakeManager();
    ~cakeManager();
    bool run (const std::string & conf_file ) final;
    void reset () final;
};

}
#endif //CA_CAKE_MANAGER_H
