
def readFile(filePath):
    with open(filePath, 'r') as file:
        lines = [line.strip() for line in file if line.strip()]

    n = int(lines[0])
    
    distance_matrix = []
    for i in range(1, n + 1):
        row = list(map(int, lines[i].split()))
        distance_matrix.append(row)
        
    flow_matrix = []
    for i in range(n + 1, 2 * n + 1):
        row = list(map(int, lines[i].split()))
        flow_matrix.append(row)
        
    coordinates = []
    for i in range(2 * n + 1, 3 * n + 1):
        parts = lines[i].replace('(', '').replace(')', '').split(',')
        coordinates.append((int(parts[0]), int(parts[1])))
        
    return n, distance_matrix, flow_matrix, coordinates

def main():
    n, dist_matrix, flow_matrix, coords = readFile('inputEx.txt')
    print("N:", n)
    print("Distance Matrix:", dist_matrix)
    print("Flow Matrix:", flow_matrix)
    print("Coordinates:", coords)


if __name__ == "__main__":
    main()