def CalcularFreq(seq):
    seq = 'ACTCTTCTGGTCCCCACAGACT'
    seqDNA = seq.upper()
    freqa = float(seqDNA.DNA.count('A')/len(seqDNA))
    return freqa

