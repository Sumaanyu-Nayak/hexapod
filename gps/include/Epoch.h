#ifndef EPOCH_H
#define EPOCH_H

#include <string>
#include <vector>

struct GNSS_Epoch {
    std::string RMC;
    std::string VTG;
    std::string GGA;
    std::vector<std::string> GSA;
    std::vector<std::string> GSV;
    std::string GLL;

    bool isComplete() const {
        return !RMC.empty() && !VTG.empty() && !GGA.empty() && !GLL.empty();
    }

    void clear() {
        RMC.clear(); VTG.clear(); GGA.clear(); GLL.clear();
        GSA.clear(); GSV.clear();
    }
};

#endif
