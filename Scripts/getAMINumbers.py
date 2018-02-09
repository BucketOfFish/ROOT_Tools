#localSetupPyAMI
#voms-proxy-init -voms atlas

import os
import ROOT
import pyAMI.client
import pyAMI.atlas.api as AtlasAPI
client = pyAMI.client.Client('atlas')
AtlasAPI.init()

file_loc = "/afs/cern.ch/work/t/tholmes/ZMETSamples/variations/"

def getSampleWeight(dsid):
    fname = ""
    files = os.listdir(file_loc)
    for f in files:
        if dsid in f: fname = f.strip("_ntupleOutput\.root\/").strip("user\.tholmes\.")
    fname = "m" + fname
    info = AtlasAPI.get_dataset_info(client, fname)[0]
    xs = float(info.get('approx_crossSection'))*float(info.get('approx_GenFiltEff'))
    return xs

print getSampleWeight('361063')
print getSampleWeight('361064')
print getSampleWeight('361065')
print getSampleWeight('361066')
print getSampleWeight('361067')
print getSampleWeight('361068')
print getSampleWeight('361073')
print getSampleWeight('361077')
print getSampleWeight('361084')
print getSampleWeight('361086')
print getSampleWeight('363089')
print getSampleWeight('363088')
print getSampleWeight('363087')
print getSampleWeight('363086')
print getSampleWeight('363085')
print getSampleWeight('363083')
print getSampleWeight('363082')
print getSampleWeight('363081')
print getSampleWeight('363080')
print getSampleWeight('363079')
print getSampleWeight('363078')
print getSampleWeight('363077')
print getSampleWeight('363076')
print getSampleWeight('363075')
print getSampleWeight('363074')
print getSampleWeight('363073')
print getSampleWeight('363072')
print getSampleWeight('363071')
print getSampleWeight('363070')
print getSampleWeight('363069')
print getSampleWeight('363068')
print getSampleWeight('363067')
print getSampleWeight('363066')
print getSampleWeight('363065')
print getSampleWeight('363064')
print getSampleWeight('363063')
print getSampleWeight('363062')
print getSampleWeight('363061')
print getSampleWeight('363060')
print getSampleWeight('363058')
print getSampleWeight('363057')
print getSampleWeight('363056')
print getSampleWeight('363055')
print getSampleWeight('363054')
print getSampleWeight('363053')
print getSampleWeight('363052')
print getSampleWeight('363051')
print getSampleWeight('363050')
print getSampleWeight('363049')
print getSampleWeight('363048')
print getSampleWeight('363047')
print getSampleWeight('363046')
print getSampleWeight('363045')
print getSampleWeight('363044')
print getSampleWeight('363043')
print getSampleWeight('363042')
