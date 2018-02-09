def is_ee(event, check_truth=False):
    passed = True
    if not (event.channel==1 and event.eetrig_match): passed = False
    if check_truth:
        n_ee = 0
        match = event.truthLepton_match_electron
        parent = event.truthLepton_parent_pdgID
        for i in xrange(event.truthLepton_n):
            if match[i] and (abs(parent[i])==23 or abs(parent[i])==24):
                n_ee += 1
        if n_ee<2: passed = False
    return passed

def is_mm(event, check_truth=False):
    passed = True
    if not (event.channel==0 and event.mmtrig_match): passed = False
    if (event.mu_isBad[0] or event.mu_isBad[1]): passed = False
    if check_truth:
        n_mm = 0
        match = event.truthLepton_match_muon
        parent = event.truthLepton_parent_pdgID
        for i in xrange(event.truthLepton_n):
            if match[i] and (abs(parent[i])==23 or abs(parent[i])==24):
                n_mm += 1
        if n_mm<2: passed = False
    return passed

def is_em(event, check_truth=False):
    passed = True
    if not (event.channel>1 and event.emtrig_match): passed = False
    if event.mu_isBad[0]: passed = False
    if check_truth:
        n_mm = 0
        n_ee = 0
        match = event.truthLepton_match_muon
        parent = event.truthLepton_parent_pdgID
        for i in xrange(event.truthLepton_n):
            if match[i] and (abs(parent[i])==23 or abs(parent[i])==24):
                n_mm += 1
        match = event.truthLepton_match_electron
        for i in xrange(event.truthLepton_n):
            if match[i] and (abs(parent[i])==23 or abs(parent[i])==24):
                n_ee += 1
        if n_mm<1 or n_ee<1: passed = False
    return passed
