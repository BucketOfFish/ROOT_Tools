#!/usr/bin/env python2

"""
2015/07/30
Jonathan Long

Merge grid samples for SUSY dilep met jet analysis

This will merge all samples in directories with the same DSID assuming "user.longjon.00266904.ph...." directory names.  This will probably fail for samples without a dsid in the name.

This will ignore samples that don't have entries in the tree, or have no branches in the tree.
---> TODO: check if putting these 'bad' files last breaks things, this would avoid loosing eventcountHist entries if we don't select any events

Assumes data has 00+runnumber in name or period in name

"""

import commands, sys, os
from ROOT import *

grepKey = "JUN15"  # user

putInDirMC = "MC"
#putInDirMC = "/afs/cern.ch/work/t/tholmes/ZMETSamples/Current_Ntuples/v00-15/MC"

dataGrepKey = "'\.00\|period'"
putInDirData = "Data"


doMC = True     # Merge MC
doData = False   # Merge Data
doSampleSorting = True  # sort samples with most branches first, and run testSamples()

copySingleFiles = True  # this will skip the hadd (and template) and just copy a single file

useHaddTemplate = False # put template first
haddTemplateMC = "haddTemplate_mc_fakes_v17.root"
haddTemplateData = "haddTemplate_data_fakes_v17.root"

# Gather IDs
uniqIDs = list()
for sample in commands.getoutput("ls | grep " + grepKey + " | grep -v " + dataGrepKey).split():
    #print sample
    uniqIDs.append(sample.split('.')[2])

list(set(uniqIDs))
print commands.getoutput("ls | grep " + grepKey + " | grep -v " + dataGrepKey).split()

# Check for duplidate folders
sampleIDs = list()
for sample in commands.getoutput("ls | grep " + grepKey).split():
    sampleIDs.append(sample.split('.')[2])



if len(sampleIDs) > len(list(set(sampleIDs))):
    print "\n##########\nWARNING: there are multiple folders with the same DSID!\n##########\n"

    sys.exit()


def testSamples(samples, tempHistFile, isMC ):
    samplesNew = ""
    nBranches = 0
    bestSample = ""
    useTempHist = False
    tempHist = TH1D()

    for sample in samples.split():
        print sample

        f = TFile(sample)

        try:
            if f.Get("outputTree").GetNbranches() > 0:
                if f.Get("outputTree").GetNbranches() > nBranches:
                    nBranches = f.Get("outputTree").GetNbranches()
                    bestSample = sample
                samplesNew += " " + sample
            else:
                # need to get histogram count
                if not useTempHist:
                    tempHist = TH1D(f.Get("EventCountHist").Clone())
                    tempHist.SetDirectory(tempHistFile)
                else:
                    tempHist.Add( f.Get("EventCountHist") )
            
                useTempHist = True
        except AttributeError:
            print "No Tree!?: " + sample + " bad file?"
            # need to get histogram count
            if not useTempHist:
                tempHist = TH1D(f.Get("EventCountHist").Clone())
                tempHist.SetDirectory(tempHistFile)
            else:
                tempHist.Add( f.Get("EventCountHist") )
                
            useTempHist = True
        
            continue
            #samplesNew += " " + sample


        f.Close()
    tempHistFile.Write()
    tempHistFile.Close()

    samplesNew = samplesNew.replace(bestSample,"")
    samplesNew = bestSample + " " + samplesNew + (" temp.root" if useTempHist else "") 

    if useHaddTemplate:
        if isMC:
            samplesNew = haddTemplateMC + " " + samplesNew
        else:
            samplesNew = haddTemplateData + " " + samplesNew

    return samplesNew

# Make folders

if not os.path.isdir( putInDirMC ):
    os.mkdir( putInDirMC )
if not os.path.isdir( putInDirData ):
    os.mkdir( putInDirData )



# merge samples
if doMC:
    #MC
    for dsid in uniqIDs:

        # these next few lines are probably outdated
        isData = False

        if dsid != dsid.lstrip("00") or "period" in dsid:
            isData = True
            dsid = dsid.lstrip("00")

        if isData:
            # actually do data later
            continue

        print "\nMerging: " + dsid
        # use entries not filesize
        samples = commands.getoutput("find *"+ dsid +"*  -type f -iname \*.root\*")

        # Just copy single files
        if len(samples.split())==1 and copySingleFiles == True:
            print "/bin/cp " + samples.split()[0] + " " + putInDirMC + "/" + dsid + ".root " 
            commands.getoutput("/bin/cp " + samples.split()[0] + " " + putInDirMC + "/" + dsid + ".root ")

            continue

        if doSampleSorting:
            # temp file to store histogram if needed
            tempHistFile = TFile("temp.root","recreate")
            samples = testSamples(samples, tempHistFile, True) 
    
        if len(samples) ==0:
            print "No Samples found for "<<str(dist)<<"!"
            continue
        
        print "hadd -f2 " + (putInDirData if isData else putInDirMC) +"/" + ("data_" if isData else "" ) +  dsid + ".root " + " ".join(samples.split())
        commands.getoutput( "hadd -f2 " + (putInDirData if isData else putInDirMC) +"/" + ("data_" if isData else "" ) +  dsid + ".root " + " ".join(samples.split()) ) 
        commands.getoutput("rm temp.root")


if doData:
    print "Merging Data\n"
    #Data
    dataFiles=""
    for sample in commands.getoutput("ls | grep " + dataGrepKey).split():
        for f in commands.getoutput("ls "+sample).split():
            dataFiles+= sample+"/"+f+" "

    tempHistFile = TFile("temp.root","recreate")
    dataFiles = testSamples(dataFiles, tempHistFile, False)
    print dataFiles
    print "hadd -f2 "+putInDirData+"/data.root " +dataFiles
    commands.getoutput("hadd -f2 "+putInDirData+"/data.root " +dataFiles)
    commands.getoutput("rm temp.root")
