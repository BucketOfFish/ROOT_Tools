#ifndef WORKSPACE_H
#define WORKSPACE_H

Class Workspace {

private:

    TString MCPath = "";
    TString dataPath = "";
    bool blinded = true;
    int luminosity = 3316;

    vector<Group> groups;

public:

    void AddGroup(Group group) {
        groups.push_back(group);
    }

    void AddSMGroups() {
        AddGroup(Zee);
        AddGroup(Zmm);
        AddGroup(Ztt);
        AddGroup(ttbar);
        AddGroup(rareTop);
        AddGroup(SherpaVV);
        AddGroup(SherpaWZ);
        AddGroup(SherpaZZ);
    }

    void AddData() {
        if(blinded)
            AddGroup(blindedData);
        else
            AddGroup(data);
    }

    int NGroups() {
        return groups.size();
    }

    void ResetGroups() {
        groups.clear();
    }

    // Merge all current groups into a single group
    void CombineGroups(TString name = "MC") {
        Group combinedGroup(name);
        for (int i=0; i<NGroups(); i++) {
            vector<TString> samples = groups[i].GetSamples();
            for (int j=0; j<samples.size(); j++) combinedGroup.AddSample(samples[j]);
        }
        ResetGroups();
        combinedGroup.SetPath(MCPath);
        AddGroup(combinedGroup);
    }
}

#endif
