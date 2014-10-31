def mgetsub(v1, v2, i,j, cs,rs, cl,rl):
    attr=v1.attrib
    o='offset';rows='rowstride';cols='colstride'
    rowl='rowlength';coll='collength'
    attr[o]   +=i*attr[cols]+j*attr[rows]
    attr[rows]*= rs; attr[cols] *= cs
    attr[rowl] = rl; attr[coll] = cl
    v2.putattrib(attr)
