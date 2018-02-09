import ROOT
from ROOT import gSystem
gSystem.Load("libSusyFitter.so")

################################################################################################
## Emma Kuwertz <Emma.Sian.Kuwertz@cern.ch                                                    ##
## File containing data-driven nominals and all theory / experimental uncertainties for Z+MET ##
## - updated estimates and uncertainties can be added here by region                          ##
################################################################################################
from systematic import Systematic
from configManager import configMgr
from math import sqrt
fakeSF=4

## Nominal buildHistos
def GetFakes(region):
    if region == "SRZ": fakes = -1.63
    if region == "SRZee": fakes = -0.39
    if region == "SRZmm": fakes = -1.24
    if region == "CRT": fakes = 35.03
    if region == "VRS": fakes = 4.80
    if region == "VRSee": fakes = 2.02
    if region == "VRSmm": fakes = 2.78
    if region == "VRT": fakes = 40.63
    if fakes<0: fakes = 0.1
    return fakes


def GetFlSym(region):
    if region == "SRZ": fs = 11.78
    if region == "SRZee": fs = 5.84
    if region == "SRZmm": fs = 5.93
    if region == "VRS": fs = 39.0
    if region == "VRSee": fs = 19.61
    if region == "VRSmm": fs = 19.40
    return fs


def GetJS(region):
    if region == "SRZ": js = 1.41
    if region == "SRZee": js = 5.84
    if region == "SRZmm": js = 5.93
    if region == "VRS": js = 39.0
    if region == "VRSee": js = 19.61
    if region == "VRSmm": js = 19.40
    return js





## Theory uncertainties
def GetDibosonUnc(region, sample):
    
    # we use the same diboson uncertainties in VRS/SRZ and VRT/CRT
    if "VRT" in region: region = "CRT"
    if "VRS" in region or "SRZ" in region: region = "SRZ"
    
    xsec_unc = [Systematic("unc_db_xsec", configMgr.weights,1.06,0.94,"user","userOverallSys"),]
    
    if 'llvv' in sample or 'WWoffZ' in sample:
        syst_dict = {
            "SRZ": [  
                Systematic("unc_db_scales", configMgr.weights,1.19,0.81,"user","userOverallSys"),
                Systematic("unc_db_pdf", configMgr.weights,1.034,0.962,"user","userOverallSys"),
                Systematic("unc_db_gen", configMgr.weights,1.71,0.29,"user","userOverallSys") ,
                ],
            "CRT": [
                Systematic("unc_db_scales", configMgr.weights,1.24,0.76,"user","userOverallSys"),
                Systematic("unc_db_pdf", configMgr.weights,1.04,0.979,"user","userOverallSys"),
                Systematic("unc_db_gen", configMgr.weights,1.55,0.45,"user","userOverallSys"),
                ],
            }
        
        systematics = syst_dict[region]
        systematics += xsec_unc
        
    elif 'WZZZ' in sample:
        syst_dict = {
            "SRZ": [
                Systematic("unc_db_gen", configMgr.weights,1.38,0.62,"user","userOverallSys"),
                Systematic("unc_db_scales", configMgr.weights,1.23,0.77,"user","userOverallSys"),
                Systematic("unc_db_pdf", configMgr.weights,1.031,0.971,"user","userOverallSys"),
                ],
            "CRT": [
                Systematic("unc_db_gen", configMgr.weights,1.07,0.93,"user","userOverallSys"),
                Systematic("unc_db_scales", configMgr.weights,1.26,0.74,"user","userOverallSys"),
                Systematic("unc_db_pdf", configMgr.weights,1.04,0.961,"user","userOverallSys"),
                ],
            }
        systematics = syst_dict[region]
        systematics += xsec_unc
    else:
        print "ERROR: GetDibosonUnc - unrecognised sample!"
    return systematics
    
    
def GetRareTopUnc(region):
    
    systematics = [
        Systematic("unc_ttv_xsec", configMgr.weights,1.22,0.78,"user","userOverallSys"),
        Systematic("unc_ttv_scales", configMgr.weights,1.13,0.87,"user","userOverallSys"),
        ]
    return systematics


def GetSingeTopUnc(region):
    
    if "VRS" in region: region = "VRS"
    if "SRZ" in region: region = "SRZ"
    
    xsec_unc = [Systematic("unc_st_xsec", configMgr.weights,1.053,0.947,"user","userOverallSys")]
    syst_dict = {
        "SRZ": [
            Systematic("unc_Wt_DS_unc", configMgr.weights,1.63,0.37,"user","userOverallSys"),
            Systematic("unc_Wt_rad_unc", configMgr.weights,1.06,0.94,"user","userOverallSys"),
            ],
        "CRT": [
            Systematic("unc_Wt_DS_unc", configMgr.weights,1.73,0.27,"user","userOverallSys"),
            Systematic("unc_Wt_rad_unc", configMgr.weights,1.10,0.90,"user","userOverallSys"),
            ],
        "VRS": [
            Systematic("unc_Wt_DS_unc", configMgr.weights,1.34,0.66,"user","userOverallSys"),
            Systematic("unc_Wt_rad_unc", configMgr.weights,1.06,0.94,"user","userOverallSys"),
            ],
        "VRT": [
            Systematic("unc_Wt_DS_unc", configMgr.weights,1.53,0.47,"user","userOverallSys"),
            Systematic("unc_Wt_rad_unc", configMgr.weights,1.06,0.94,"user","userOverallSys"),
            ],
        }
    systematics = syst_dict[region]
    systematics += xsec_unc
    return systematics

def GetTopUnc(region):
    
    if "VRS" in region: region = "VRS"
    if "SRZ" in region: region = "SRZ"
    
    syst_dict = {
        "SRZ": [
            Systematic("unc_srz_top_theo_unc", configMgr.weights,1.3,0.7,"user","userOverallSys"),
            ],
        "VRS": [
            Systematic("unc_vrs_top_theo_unc", configMgr.weights,1.29,0.71,"user","userOverallSys"),
            ],
        "VRT": [
            Systematic("unc_vrt_top_theo_unc", configMgr.weights,1.074,0.926,"user","userOverallSys"),
            ],
        }
    systematics = syst_dict[region]
    return systematics

def GetZjetsUnc():
    
    xsec_unc = [Systematic("unc_zjets_xsec", configMgr.weights,1.05,0.95,"user","userOverallSys")]
    return xsec_unc

def GetFakesUnc(region,fakeSF=1):
    
    fakeNom = GetFakes(region)
    syst_dict = {
        "SRZ": [
            Systematic("fakes_srz_syst", configMgr.weights,(sqrt(0.14**2 + 0.4**2)/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            Systematic("fakes_srz_stat", configMgr.weights,(1.12/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            ],
        "SRZmm": [
            Systematic("fakes_srz_syst", configMgr.weights,(sqrt(0.4**2 + 0.36**2)/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            Systematic("fakes_srz_stat", configMgr.weights,(0.84/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            ],
        "SRZee": [
            Systematic("fakes_srz_syst", configMgr.weights,(sqrt(0.03**2 + 0.03**2)/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            Systematic("fakes_srz_stat", configMgr.weights,(0.74/fakeNom)/fakeSF,fakeNom*fakeSF,"user","userOverallSys"),
            ],
        "CRT": [
            Systematic("fakes_crt_syst", configMgr.weights,1+(sqrt(9.49**2 + 7.48**2)/fakeNom),1-(sqrt(7.43**2 + 11.84**2)/fakeNom),"user","userOverallSys"),
            Systematic("fakes_crt_stat", configMgr.weights,1+(7.13/fakeNom),1-(7.13/fakeNom),"user","userOverallSys"),
            ],
        "VRS": [
            Systematic("fakes_vrs_syst", configMgr.weights,1+(sqrt(1.11**2 + 0.1**2)/fakeNom),1-(sqrt(0.85**2 + 2.86**2)/fakeNom),"user","userOverallSys"),
            Systematic("fakes_vrs_stat", configMgr.weights,1+2.98/fakeNom,1-(2.98/fakeNom),"user","userOverallSys"),
            ],
        "VRSee": [
            Systematic("fakes_vrs_syst", configMgr.weights,1+(sqrt(0.87**2 + 0.05**2)/fakeNom),1-(sqrt(0.65**2 + 2.73**2)/fakeNom),"user","userOverallSys"),
            Systematic("fakes_vrs_stat", configMgr.weights,1+1.80/fakeNom,1-(1.80/fakeNom),"user","userOverallSys"),
            ],
        "VRSmm": [
            Systematic("fakes_vrs_syst", configMgr.weights,1+(sqrt(0.70**2 + 1.87**2)/fakeNom),1-(sqrt(0.55**2 + 1.36**2)/fakeNom),"user","userOverallSys"),
            Systematic("fakes_vrs_stat", configMgr.weights,1+(2.38/fakeNom),1-(2.38/fakeNom),"user","userOverallSys"),
            ],
        "VRT": [
            Systematic("fakes_vrt_syst", configMgr.weights,1+(sqrt(5.5**2 + 0.37**2)/fakeNom),1-(sqrt(10.39**2 + 24.68**2)/fakeNom),"user","userOverallSys"),
            Systematic("fakes_vrt_stat", configMgr.weights,1+(10.83/fakeNom),1-(10.83/fakeNom),"user","userOverallSys"),
            ],
        }
    systematics = syst_dict[region]
    return systematics

def GetFlSymUnc(region):
    fsNom = GetFlSym(region)
    syst_dict = {
        "SRZ": [
            Systematic("unc_srz_fs_stat", configMgr.weights,1+(2.44/fsNom),1-(2.44/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_srz_fs_syst", configMgr.weights,1+(sqrt(0.64**2 + 0.91**2 + 0.1**2 + 0.26**2)/fsNom),1-(sqrt(0.64**2 + 0.91**2 + 0.1**2 + 0.26**2)/fsNom),"user","userOverallSys"),
            ],
        "SRZee": [
            Systematic("unc_srz_fs_stat", configMgr.weights,1+(1.21/fsNom),1-(1.21/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_srz_fs_syst", configMgr.weights,1+(sqrt(0.4**2 + 0.51**2 + 0.05**2 + 0.13**2)/fsNom),1-(sqrt(0.4**2 + 0.51**2 + 0.05**2 + 0.13**2)/fsNom),"user","userOverallSys"),
            ],
        "SRZmm": [
            Systematic("unc_srz_fs_stat", configMgr.weights,1+(1.24/fsNom),1-(1.24/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_fs_syst", configMgr.weights,1+(sqrt(0.54**2 + 0.41**2 + 0.05**2 + 0.13**2)/fsNom),1-(sqrt(0.54**2 + 0.41**2 + 0.05**2 + 0.13**2)/fsNom),"user","userOverallSys"),
            ],
        "VRS": [
            Systematic("unc_vrs_fs_stat", configMgr.weights,1+(3.83/fsNom),1-(3.83/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_fs_syst", configMgr.weights,1+(sqrt(2.13**2 + 2.81**2 + 0.31**2 + 0.88**2)/fsNom),1-(sqrt(2.13**2 + 2.81**2 + 0.31**2 + 0.88**2)/fsNom),"user","userOverallSys"),
            ],
        "VRSee": [
            Systematic("unc_vrs_fs_stat", configMgr.weights,1+(1.94/fsNom),1-(1.94/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_fs_syst", configMgr.weights,1+(sqrt(1.32**2 + 1.61**2 + 0.16**2 + 0.44**2)/fsNom),1-(sqrt(1.32**2 + 1.61**2 + 0.16**2 + 0.44**2)/fsNom),"user","userOverallSys"),
            ],
        "VRSmm": [
            Systematic("unc_vrs_fs_stat", configMgr.weights,1+(1.89/fsNom),1-(1.89/fsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_fs_syst", configMgr.weights,1+(sqrt(1.27**2 + 1.21**2 + 0.15**2 + 0.44**2)/fsNom),1-(sqrt(1.27**2 + 1.21**2 + 0.15**2 + 0.44**2)/fsNom),"user","userOverallSys"),
            ],
        }
    systematics = syst_dict[region]
    return systematics



def GetJSUnc(region):
    jsNom = GetJS(region)
    syst_dict = {
        "SRZ": [
            Systematic("unc_srz_js_stat", configMgr.weights,1.2176,0.7824,"user","shapeSys",constraint="Poisson"),
            Systematic("unc_srz_js_syst", configMgr.weights,1.7196,0.2804,"user","userOverallSys"),
            ],
        "SRZee": [
            Systematic("unc_srz_js_stat", configMgr.weights,1+(1.21/jsNom),1-(1.21/jsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_srz_js_syst", configMgr.weights,1+(sqrt(0.4**2 + 0.51**2 + 0.05**2 + 0.13**2)/jsNom),1-(sqrt(0.4**2 + 0.51**2 + 0.05**2 + 0.13**2)/jsNom),"user","userOverallSys"),
            ],
        "SRZmm": [
            Systematic("unc_srz_js_stat", configMgr.weights,1+(1.24/jsNom),1-(1.24/jsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_js_syst", configMgr.weights,1+(sqrt(0.54**2 + 0.41**2 + 0.05**2 + 0.13**2)/jsNom),1-(sqrt(0.54**2 + 0.41**2 + 0.05**2 + 0.13**2)/jsNom),"user","userOverallSys"),
            ],
        "VRS": [
            Systematic("unc_vrs_js_stat", configMgr.weights,1+(3.83/jsNom),1-(3.83/jsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_js_syst", configMgr.weights,1+(sqrt(2.13**2 + 2.81**2 + 0.31**2 + 0.88**2)/jsNom),1-(sqrt(2.13**2 + 2.81**2 + 0.31**2 + 0.88**2)/jsNom),"user","userOverallSys"),
            ],
        "VRSee": [
            Systematic("unc_vrs_js_stat", configMgr.weights,1+(1.94/jsNom),1-(1.94/jsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_js_syst", configMgr.weights,1+(sqrt(1.32**2 + 1.61**2 + 0.16**2 + 0.44**2)/jsNom),1-(sqrt(1.32**2 + 1.61**2 + 0.16**2 + 0.44**2)/jsNom),"user","userOverallSys"),
            ],
        "VRSmm": [
            Systematic("unc_vrs_js_stat", configMgr.weights,1+(1.89/jsNom),1-(1.89/jsNom),"user","shapeSys",constraint="Poisson"),
            Systematic("unc_vrs_js_syst", configMgr.weights,1+(sqrt(1.27**2 + 1.21**2 + 0.15**2 + 0.44**2)/jsNom),1-(sqrt(1.27**2 + 1.21**2 + 0.15**2 + 0.44**2)/jsNom),"user","userOverallSys"),
            ],
        }
    systematics = syst_dict[region]
    return systematics



            

# Experimental uncertainties
def GetExperimentalUnc():
    trigUpWeights   = ['(2.*trigweight-trigweight_down)','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    trigDownWeights = ['trigweight_down','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    
    muEffStatUp = ['mu_weight_MUON_EFF_STAT__1up','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffStatDown = ['mu_weight_MUON_EFF_STAT__1down','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffStatLowPtUp = ['mu_weight_MUON_EFF_STAT_LOWPT__1up','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffStatLowPtDown = ['mu_weight_MUON_EFF_STAT_LOWPT__1down','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffSysUp = ['mu_weight_MUON_EFF_SYS__1up','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffSysDown = ['mu_weight_MUON_EFF_SYS__1down','sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffSysLowPtUp = ['mu_weight_MUON_EFF_SYS_LOWPT__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
    muEffSysLowPtDown = ['mu_weight_MUON_EFF_SYS_LOWPT__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']
        #['mu_weight_MUON_EFF_TrigStatUncertainty__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight'],  
        #['mu_weight_MUON_EFF_TrigSystUncertainty__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight'],  
    muEffIsoStatUp = ['mu_weight_MUON_ISO_STAT__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                 
    muEffIsoStatDown = ['mu_weight_MUON_ISO_STAT__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                 
    muEffIsoSysUp = ['mu_weight_MUON_ISO_SYS__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                  
    muEffIsoSysDown = ['mu_weight_MUON_ISO_SYS__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                  
    puUp = ['eventWeight_PRW_DATASF__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                  
    puDown = ['eventWeight_PRW_DATASF__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']                  
    elEffIdUp = ['el_weight_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']              
    elEffIdDown = ['el_weight_EL_EFF_ID_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']              
    elEffIsoUp = ['el_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']             
    elEffIsoDown = ['el_weight_EL_EFF_Iso_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']             
    elEffRecoUp = ['el_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']            
    elEffRecoDown = ['el_weight_EL_EFF_Reco_TOTAL_1NPCOR_PLUS_UNCOR__1down', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']            
        #['el_weight_EL_EFF_TriggerEff_TOTAL_1NPCOR_PLUS_UNCOR__1up', 'sampleWeight','eventWeight','lep_weight[0]','lep_weight[1]','pileupWeight']      
    
    ExpUnc =  [
        
        
        Systematic('muEffIsoStat',configMgr.weights,muEffIsoStatUp,muEffIsoStatDown ,'weight', 'overallNormHistoSys'),
        Systematic('muEffIsoSyst',configMgr.weights,muEffIsoSysUp,muEffIsoSysDown ,'weight', 'overallNormHistoSys'),
        Systematic('pileup',configMgr.weights,puUp,puDown ,'weight', 'overallNormHistoSys'),
        Systematic('elEffId',configMgr.weights,elEffIdUp,elEffIdDown ,'weight', 'overallNormHistoSys'),
        Systematic('elEffIso',configMgr.weights,elEffIsoUp,elEffIsoDown ,'weight', 'overallNormHistoSys'),
        Systematic('elEffReco',configMgr.weights,elEffRecoUp,elEffRecoDown ,'weight', 'overallNormHistoSys'),
        Systematic('muEffStat',configMgr.weights,muEffStatUp,muEffStatDown ,'weight', 'overallNormHistoSys'),
        Systematic('muEffStatLowPt',configMgr.weights,muEffStatLowPtUp,muEffStatLowPtDown ,'weight', 'overallNormHistoSys'),
        Systematic('muEffSys',configMgr.weights,muEffSysUp,muEffSysDown ,'weight', 'overallNormHistoSys'),
        Systematic('muEffSysLowPt',configMgr.weights,muEffSysLowPtUp,muEffSysLowPtDown ,'weight', 'overallNormHistoSys'),
        

        Systematic('EG_RES',           '', '_EG_RESOLUTION_ALL__1up',                  '_EG_RESOLUTION_ALL__1down',                      'tree', 'histoSys'),
        Systematic('EG_SCALE',         '', '_EG_SCALE_ALL__1up',                       '_EG_SCALE_ALL__1down',                           'tree', 'histoSys'),
        #        Systematic('EL_EFF_TRIG',      '', '_EL_EFF_Trigger_TotalCorrUncertainty__1up','_EL_EFF_Trigger_TotalCorrUncertainty__1down',    'tree', 'histoSys'),
        Systematic('JES_NP1',          '', '_JET_GroupedNP_1__1up',                    '_JET_GroupedNP_1__1down',                        'tree', 'histoSys'),
        Systematic('JES_NP2',          '', '_JET_GroupedNP_2__1up',                    '_JET_GroupedNP_2__1down',                        'tree', 'histoSys'),
        Systematic('JES_NP3',          '', '_JET_GroupedNP_3__1up',                    '_JET_GroupedNP_3__1down',                        'tree', 'histoSys'),
        Systematic('JES_EtaInterCalib','', '_JET_EtaIntercalibration_NonClosure__1up', '_JET_EtaIntercalibration_NonClosure__1down',     'tree', 'histoSys'),
        Systematic('JER',              '', '_JET_JER_SINGLE_NP__1up',                  '_JET_JER_SINGLE_NP__1up',                        'tree', 'histoSys'),
        Systematic('MET_RES',          '', '_MET_SoftTrk_ResoPara',                    '_MET_SoftTrk_ResoPerp',                          'tree', 'histoSys'),
        Systematic('MET_SCALE',        '', '_MET_SoftTrk_ScaleUp',                     '_MET_SoftTrk_ScaleDown',                         'tree', 'histoSys'),
        Systematic('MUON_ID',          '', '_MUONS_ID__1up',                           '_MUONS_ID__1down',                               'tree', 'histoSys'),
        Systematic('MUON_MS',          '', '_MUONS_MS__1up',                           '_MUONS_MS__1down',                               'tree', 'histoSys'),
        Systematic('MUON_SCALE',       '', '_MUONS_SCALE__1up',                        '_MUONS_SCALE__1down',                            'tree', 'histoSys'),
        #        Systematic('MU_TRIG_STAT',     '', '_MUON_EFF_TrigStatUncertainty__1up',       '_MUON_EFF_TrigStatUncertainty__1down',           'tree', 'histoSys'),
        #        Systematic('MU_TRIG_SYST',     '', '_MUON_EFF_TrigSystUncertainty__1up',       '_MUON_EFF_TrigSystUncertainty__1down',           'tree', 'histoSys'),
        #        Systematic('TriggerSF',configMgr.weights,trigUpWeights,trigDownWeights,'weight','overallNormHistoSys'),

        ]
    
    return ExpUnc
