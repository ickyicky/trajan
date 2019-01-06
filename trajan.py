#trajan python
#this simple script is an simplified implementations of graph with implemented "mosty_rozlegle"
#property. Most rozlegly (broad bridge from polish) is an edge of the graph, after wchich
#deletion (including vertexes it's connected to) the grapth is no longer connected.
#The main algorithm is based on Tarjan algorithm.

from collections import defaultdict

class Graph:
    class Vertex():
        def __init__(self, name):
            self.connected = []
            self.name = name

        def connect(self, vertex):
            if not vertex in self.connected:
                self.connected.append(vertex)


    def __init__(self, edges = []):
        self.vertexes = set()

        for edge in edges:
            first = self.find_v(edge[0])
            if not first:
                first = self.Vertex(edge[0])
                self.vertexes.add(first)

            second = self.find_v(edge[1])
            if not second:
                second = self.Vertex(edge[1])
                self.vertexes.add(second)

            first.connect(second)
            second.connect(first)

    def trojan(self, v, not_included, values=None, trojans=None, current_num=1, parent=None):
        if not values:
            values = defaultdict(int)
        if not trojans:
            trojans = set()
        low = current_num
        values[v] = current_num
        current_num = current_num + 1
        children = 0
        is_trojan = False

        for vc in [c for c in v.connected if c != not_included and c != parent]:
            num = values[vc]
            if num == 0:
                #as we use defaultdict, the vertex with assigned default value(0) wasnt visited
                trojans = self.trojan(vc, not_included, values, trojans, current_num, v)
                num = values[vc]
                if num >= low:
                    is_trojan = True
                children = children + 1
            if num < low:
                low = num

        if is_trojan:
            if parent:
                trojans.add(v)
            elif children >= 2:
                trojans.add(v)

        values[v] = low

        if any(values[x] == 0 for x in self.vertexes):
            return not_included.connected

        return trojans

    @property
    def mosty_rozlegle(self):
        found = set()

        for v in self.vertexes :
            if len(v.connected) >= 2:
                #very basic observation: if the vertex isn't connected with at least 2 other
                #vertexes, it can't be an end of "most rozlegly"
                for trojan in self.trojan(v.connected[0], v):
                    if not (trojan.name,v.name) in found:
                        found.add((v.name,trojan.name))

        return found

    def find_v(self, name):
        found = [v for v in self.vertexes if v.name == name]
        if len(found) == 1:
            return found[0]
        return None


if __name__ == '__main__':
    import fileinput

    edges = []
    for a in fileinput.input():
        for line in a.split('\n'):
            values = line.split(' ')
            if len(values) > 1:
                edges.append((values[0], values[1]))

    graf = Graph(edges)
    print(graf.mosty_rozlegle)
