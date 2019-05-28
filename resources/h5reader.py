import h5py
import json
import numpy as np
# import pysnooper

class NpEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.integer):
            return int(obj)
        elif isinstance(obj, np.floating):
            return float(obj)
        elif isinstance(obj, np.ndarray):
            return obj.tolist()
        else:
            return super(NpEncoder, self).default(obj)

# @pysnooper.snoop()
def read(fileName):
    f = h5py.File(fileName)
    dic = {}
    for key in list(f.keys()):
        if key.startswith("conv"):
            dic[key] = {}
            dic[key]["bias"] = list(f[key][key]["bias:0"])
            dic[key]["weights"] = np.array(list(f[key][key]["kernel:0"])).transpose(3, 2, 0, 1)
        if key.startswith("dense"):
            dic[key] = {}
            dic[key]["bias"] = list(f[key][key]["bias:0"])
            dic[key]["weights"] = np.array(list(f[key][key]["kernel:0"])).T
    js = json.dumps(dic, cls=NpEncoder)
    with open("weights.json", 'w') as w:
        w.write(js)
    f.close()

if __name__ == "__main__":
    name = "weights.h5"
    read(name)