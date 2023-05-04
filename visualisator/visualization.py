import polyscope as ps
import numpy as np

# Initialize polyscope, creating graphics contexts and constructing a window.
ps.init()

#reading from files
with open('edges.txt') as f:
    e = f.readlines()

with open('nodes.txt') as f:
    n = f.readlines()

indicate  = []
positions = []
labels    = []

#extracting data from the text
for i in n:
    tmp = i.split(',')
    tmp= list(map(int, tmp[1:4]))
    indicate.append(tmp[0])
    positions.append(tmp)
    labels.append(tmp[-1])

#converasion to numpy
positions= np.array(positions)

edges     = []

for i in e:
    tmp = i.split(',')
    tmp= list(map(int, tmp[:2]))
    edges.append(tmp)

edges = np.array(edges)


# visualize!
ps_net = ps.register_curve_network("my network", positions, edges, 
                           material='candy', radius=0.02, color=(1., 0., 0.))

vals_edge = np.random.rand(len(edges), 3)
ps_net.add_color_quantity("rand vals2", vals_edge, defined_on='edges')

vals_node = np.random.rand(len(positions), 3)
ps_net.add_color_quantity("rand vals", vals_node, enabled=True)

ps.show()



