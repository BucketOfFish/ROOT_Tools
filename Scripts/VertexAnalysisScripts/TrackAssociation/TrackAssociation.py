import matplotlib.pyplot as plt
import numpy as np
import re
import collections

class Track:
    d0 = 0
    z0 = 0
    phi = 0
    eta = 0
    qOverP = 0
    pt = 0
    isHS = False
    recoOrigin = None #which reco vertex this track is associated to
    truthOrigin = None #which truth vertex this track is associated to
    def __init__(self, d0, z0, phi, eta, qOverP, pt):
        self.d0 = d0
        self.z0 = z0
        self.phi = phi
        self.eta = eta
        self.qOverP = qOverP
        self.pt = pt

class Vertex:
    x = 0
    y = 0
    z = 0
    isHS = False
    color = 'red'
    tracks = []
    def __init__(self, x=0, y=0, z=0):
        self.x = x
        self.y = y
        self.z = z
    def isIn(self, collection):
        for vertex in collection:
            if self.x==vertex.x and self.y==vertex.y and self.z==vertex.z:
                return vertex
        return None
    def addTo(self, collection):
        existingObject = self.isIn(collection)
        if not existingObject:
            collection.append(self)
            return self
        else:
            return existingObject

def drawPlots(fileName):
    ###############
    ### Options ###
    ###############
    highlightHS = False #gray out all vertices except reco HS

    #############################################
    ### Open file, set up plot and containers ###
    #############################################
    file = open("TrackAssociation/"+fileName+".txt")
    recoVertices = []
    truthVertices = []
    tracks = []
    plt.figure(figsize=(20,12))
    currentVertex = None
    HSVertex = None

    while True:
        ###############################
        ### Read in lines from file ###
        ###############################
        line = file.readline().rstrip('\n')
        if not line:
            break
        values = re.split(r'\t+', line)

        if values[0]=="New Vertex" or values[0]=="HS Vertex":
            #########################
            ### Create new vertex ###
            #########################
            recoX = float(values[1])
            recoY = float(values[2])
            recoZ = float(values[3])
            currentVertex = Vertex(recoX, recoY, recoZ)
            currentVertex.addTo(recoVertices)
            if values[0]=="HS Vertex":
                currentVertex.isHS = True
                HSVertex = currentVertex
        else:
            ########################
            ### Create new track ###
            ########################
            d0 = float(values[0])
            z0 = float(values[1])
            phi = float(values[2])
            eta = float(values[3])
            qOverP = float(values[4])
            pt = float(values[5])
            newTrack = Track(d0, z0, phi, eta, qOverP, pt)
            newTrack.recoOrigin = currentVertex
            currentVertex.tracks.append(newTrack)
            tracks.append(newTrack)
            if currentVertex.isHS:
                newTrack.isHS = True
            #############################################
            ### Create new truth vertex and add track ###
            #############################################
            truthX = float(values[6])
            truthY = float(values[7])
            truthZ = float(values[8])
            if truthX==-999: #not associated to any truth vertex
                continue
            truthVertex = Vertex(truthX, truthY, truthZ)
            newTrack.truthOrigin = truthVertex.addTo(truthVertices)
            if currentVertex.isHS:
                truthVertex.isHS = True
            truthVertex.tracks.append(newTrack)

    #####################
    ### Set up colors ###
    #####################
    colors = []
    rgbcolors = [(240,163,255),(0,117,220),(153,63,0),(76,0,92),(25,25,25),(0,92,49),(43,206,72),(255,204,153),(128,128,128),(148,255,181),(143,124,0),(157,204,0),(194,0,136),(0,51,128),(255,164,5),(255,168,187),(66,102,0),(255,0,16),(94,241,242),(0,153,143),(224,255,102),(116,10,255),(153,0,0),(255,255,128),(255,255,0),(255,80,5)]
    for rgbcolor in rgbcolors:
        colors.append('#%02x%02x%02x' % rgbcolor)
    ############################
    ### Assign vertex colors ###
    ############################
    colorCount = 0
    for vertex in recoVertices:
        if highlightHS and vertex.isHS:
            vertex.color = 'red'
        else:
            colorCount = (colorCount+1)%len(colors) #move to the next color
            vertex.color = colors[colorCount]
    colorCount = 0
    for vertex in truthVertices:
        colorCount = (colorCount+1)%len(colors) #move to the next color
        vertex.color = colors[colorCount]
    ###################
    ### Draw tracks ###
    ###################
    for track in tracks:
        ################################################
        ### Calculate track slopes and intersections ###
        ################################################
        d0 = track.d0
        z0 = track.z0
        phi = track.phi
        eta = track.eta
        theta = 2*np.arctan(np.exp(-eta)) #calculations based on http://hepunx.rl.ac.uk/~adye/thesis/html/node46.html
        yOffset = -d0*np.cos(phi)
        xOffset = d0*np.sin(phi)
        yzSlope = 1/np.tan(theta)
        xzSlope = 1/(np.tan(theta)*np.tan(phi)) #tan(phi) = y/x; tan(theta) = z/y; x/z = 1/[tan(phi)*tan(theta)]
        y1 = (-180-z0)*yzSlope+yOffset
        y2 = (180-z0)*yzSlope+yOffset
        x1 = (-180-z0)*xzSlope+xOffset
        x2 = (180-z0)*xzSlope+xOffset
        ###################
        ### Draw tracks ###
        ###################
        if highlightHS and not track.isHS: #don't draw non-HS tracks when highlightHS==True
            pass
        else:
            trackColor = track.recoOrigin.color
            plt.subplot(411)
            plt.plot([-180, 180], [y1, y2], color=trackColor, linestyle='-', linewidth=1, zorder=1)
            plt.subplot(413)
            plt.plot([-180, 180], [x1, x2], color=trackColor, linestyle='-', linewidth=1, zorder=1)
            if not track.truthOrigin: #no associated truth vertex
                continue
            trackColor = track.truthOrigin.color
            plt.subplot(412)
            plt.plot([-180, 180], [y1, y2], color=trackColor, linestyle='-', linewidth=1, zorder=1)
            plt.subplot(414)
            plt.plot([-180, 180], [x1, x2], color=trackColor, linestyle='-', linewidth=1, zorder=1)
    ##########################
    ### Draw reco vertices ###
    ##########################
    for vertex in recoVertices:
        if highlightHS and not vertex.isHS: #don't draw non-HS vertices when highlightHS==True
            pass
        else:
            plt.subplot(411)
            plt.scatter(vertex.z, vertex.y, s=80, facecolors=vertex.color, edgecolors='b', zorder=2)
            plt.subplot(413)
            plt.scatter(vertex.z, vertex.x, s=80, facecolors=vertex.color, edgecolors='b', zorder=2)
    ###########################
    ### Draw truth vertices ###
    ###########################
    for vertex in truthVertices:
        if highlightHS and not vertex.isHS: #do not draw non-HS vertices if highlightHS==True
            pass
        else:
            plt.subplot(412)
            plt.scatter(vertex.z, vertex.y, s=80, facecolors=vertex.color, edgecolors='b', zorder=2)
            plt.subplot(414)
            plt.scatter(vertex.z, vertex.x, s=80, facecolors=vertex.color, edgecolors='b', zorder=2)

    # print(max(list(truthHSVertices.values())))
    # print(truthHSVertices.keys())

    #####################################
    ### Plot titles, ranges, and axes ###
    #####################################
    if highlightHS:
        xRangeLow = HSVertex.z-30
        xRangeHigh = HSVertex.z+30
    else:
        xRangeLow = -120
        xRangeHigh = 120
    plt.subplot(411)
    plt.xticks(np.arange(-180, 180, 30))
    plt.xlim([xRangeLow,xRangeHigh])
    plt.ylim([-5,5])
    plt.title("y-z Slice with Reco Tracks and Reco Vertices")
    plt.subplot(412)
    plt.xticks(np.arange(-180, 180, 30))
    plt.xlim([xRangeLow,xRangeHigh])
    plt.ylim([-5,5])
    plt.title("y-z Slice with Reco Tracks and Truth Vertices")
    plt.subplot(413)
    plt.xticks(np.arange(-180, 180, 30))
    plt.xlim([xRangeLow,xRangeHigh])
    plt.ylim([-5,5])
    plt.title("x-z Slice with Reco Tracks and Reco Vertices")
    plt.subplot(414)
    plt.xticks(np.arange(-180, 180, 30))
    plt.xlim([xRangeLow,xRangeHigh])
    plt.ylim([-5,5])
    plt.title("x-z Slice with Reco Tracks and Truth Vertices")
    if highlightHS:
        plt.savefig("TrackAssociation/Plots/"+fileName+"_HS.pdf")
    else:
        plt.savefig("TrackAssociation/Plots/"+fileName+"_Full.pdf")
    plt.close()

for i in range(0,30):
    drawPlots("TrackAssociation_"+str(i))
