import os

def read_from_file():

    directory_path = "./File"
    f = os.path.join(directory_path, "ALSEN_mathcad" + ".csv")

    lines = []
    y_res = []
    with open(f, 'r') as ff:
        for line in ff.readlines():
            l = line.strip()
            lines.append(float(l))
#        print (lines)

        for i in range (3*8000):
            y_res.append(lines[i])
#    print (len(y_res))

    return y_res

#read_from_file()
