#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Vector.h"
#include "Stack.h"
#include "Queue.h"
#include "Graph.h"


struct Point{
	int x, y;
	Point(){x = y = -1;}
	Point(int x, int y): x(x), y(y){}
	
	bool operator == (const Point &other)const{
		return (x == other.x && y == other.y);
	}
	Point operator-(const Point& other) const {
	    return Point(x - other.x, y - other.y);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const Point& p) {
        os <<  p.x << "," << p.y ;
        return os;
	}
	
	bool areNeighbors(const Point& p2) {
	    int dx = x - p2.x;
	    int dy = y - p2.y;
	    return ((dx == 1 && dy == 0) || 
				(dx == 0 && dy == 1) || 
				(dx == -1 && dy == 0) || 
				(dx == 0 && dy == -1) );
	}
};

struct Node {
    Point loc;
    int type;
    bool visited = false;
    Vector<Point> adj;

    Node() : loc(Point()), type(-1) {}
    Node(Point loc, int type) : loc(loc), type(type) {}

    bool operator==(const Node& other) const {
        return loc == other.loc && type == other.type;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node& n) {
        os << "(" << n.loc.x << ", " << n.loc.y << ")";
        return os;
    }
};


class Maze {
public:
    Node* start;
    Node* end;
    Point startp;
    Point endp;

    // Constructor to initialize with filename
    Maze(const std::string& filename) : start(nullptr), end(nullptr), rows(0), cols(0) {
        if (!readFromFile(filename)) {
            std::cerr << "Failed to load the maze from file: " << filename << std::endl;
        }
    }

    // Destructor to deallocate memory
    ~Maze() = default;

    // Function to read the matrix from a file
    bool readFromFile(const std::string& filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }

    std::string line;
    rows = 0;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        Vector<Node> rowVector;
        int col = 0;

        while (std::getline(iss, token, ',')) {
            int type = std::stoi(token);
            Node node = Node(Point(rows, col), type);
            rowVector.push_back(node);

            if (type == 2) {
                startp = Point(rows,col);
            } else if (type == 3) {
                endp = Point(rows, col);
            }
            col++;
        }

        matrix.push_back(rowVector);
        cols = col;  // Update cols for the first row to set the number of columns
        rows++;
    }
    start = &matrix[startp.x][startp.y];
    end = &matrix[endp.x][endp.y];

    file.close();
    initializeAdjacency();
    return true;
}

    // Function to display the matrix
    void display() const {
        if (!matrix.empty()) {
            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    std::cout << ((matrix[i][j].type == 0) ? "#" : ".") << " ";
                }
                std::cout << std::endl;
            }
        } else {
            std::cerr << "Error: Maze not loaded." << std::endl;
        }
    }

    Node& operator()(int row, int col) {
        static Node invalidNode = Node();
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Maze index out of bounds" << std::endl;
            return invalidNode;
        }
        return matrix[row][col];
    }

    const Node& operator()(int row, int col) const {
        static Node invalidNode = Node();
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Maze index out of bounds" << std::endl;
            return invalidNode;
        }
        return matrix[row][col];
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

private:
    Vector<Vector<Node>> matrix;
    int rows;
    int cols;

    void initializeAdjacency() {
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                Node& node = matrix[row][col];
                if (node.type != 0) { 
                    addAdjacentNodes(node);
                }
            }
        }
    }

    void addAdjacentNodes(Node& node) {
        static const Point directions[] = {
            Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1)
        };
        for (const Point& dir : directions) {
            Point neighborLoc = Point(node.loc.x + dir.x, node.loc.y + dir.y);
            if (isInBounds(neighborLoc.x, neighborLoc.y) && matrix[neighborLoc.x][neighborLoc.y].type != 0) {
                node.adj.push_back(neighborLoc);
            }
        }
    }

    bool isInBounds(int x, int y) const {
        return x >= 0 && x < rows && y >= 0 && y < cols;
    }
};

class Solvers {
public:
    Vector<Point> withDFS(Graph<Node>& graph, Node& start, Node& end) {
        Vector<Point> path;
        Vector<bool> visited(graph.getVertices().getSize(), false);
        
        Stack<int> stack;
        
        int startIndex = -1;
        int endIndex = -1;
        
        for (int i = 0; i < graph.getVertices().getSize(); ++i) {
            if (graph.getVertices()[i].data == start) {
                startIndex = i;
            }
            if (graph.getVertices()[i].data == end) {
                endIndex = i;
            }
        }

        if (startIndex == -1 || endIndex == -1) {
            std::cerr << "Start or end node not found in the graph." << std::endl;
            return path;
        }

        stack.push(startIndex);

        while (!stack.isEmpty()) {
            int current = stack.pop();
            if (!visited[current]) {
                path.push_back(graph.getVertices()[current].data.loc);
                visited[current] = true;

                if (current == endIndex) {
                    return path; // Path found
                }

                for (int i = graph.getVertices()[current].edges.getSize() - 1; i >= 0; --i) {
                    int neighbor = graph.getVertices()[current].edges[i];
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }

        std::cerr << "No path found from start to end using DFS." << std::endl;
        return Vector<Point>();
    }

    Vector<Point> withBFS(Graph<Node>& graph, Node& start, Node& end) {
        Vector<Point> path;
        Vector<bool> visited(graph.getVertices().getSize(), false);
        
        Vector<int> previous(graph.getVertices().getSize(), -1);
        
        Queue<int> queue;

        int startIndex = -1;
        int endIndex = -1;
        
        for (int i = 0; i < graph.getVertices().getSize(); ++i) {
            if (graph.getVertices()[i].data == start) {
                startIndex = i;
            }
            if (graph.getVertices()[i].data == end) {
                endIndex = i;
            }
        }

        if (startIndex == -1 || endIndex == -1) {
            std::cerr << "Start or end node not found in the graph." << std::endl;
            return path;
        }

        queue.enqueue(startIndex);
        visited[startIndex] = true;
        while (!queue.isEmpty()) {
            int current = queue.peek();
            queue.dequeue();
            
            if (current == endIndex) {
                // Path found, reconstruct the path
                for (int at = endIndex; at != -1; at = previous[at]) {
                    path.push_back(graph.getVertices()[at].data.loc);
                }
                // Reverse the path to start from the beginning
                Vector<Point> reversedPath;
                for (int i = path.getSize() - 1; i >= 0; --i) {
                    reversedPath.push_back(path[i]);
                    
                }
                return reversedPath;
            }

            for (int i = 0; i < graph.getVertices()[current].edges.getSize(); ++i) {
                int neighbor = graph.getVertices()[current].edges[i];
                if (!visited[neighbor]) {
                    queue.enqueue(neighbor);
                    visited[neighbor] = true;
                    previous[neighbor] = current;
                }
            }
        }

        std::cerr << "No path found from start to end using BFS." << std::endl;
        return Vector<Point>();
    }

};
void savePathToFile(const Vector<Point>& path, const std::string& filename) {
	Point left(0, -1);
	Point right(0, 1);
	Point up(-1, 0);
	Point down(1, 0);
	
	
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    if (path.getSize() == 0) {
        file << "No path found." << std::endl;
        file.close();
        return;
    }

    int totalCost = 0;
    for (int i = 0; i < path.getSize(); ++i) {
        file << "(" << path[i] << " - " << totalCost + 1 << ")";
        file << " -> ";
        totalCost++;

        if (i> 0 && i < path.getSize() - 1) {
        	Point prev = path[i-1];
            Point curr = path[i];
            Point next = path[i + 1];
            if(prev - curr == curr - next)  continue;
            if (prev.x == curr.x + 1 && prev.y == curr.y) {
                file << "yukarý\n";
            } else if (prev.x == curr.x - 1 && prev.y == curr.y) {
                file << "aþaðý\n";
            } else if (prev.y == curr.y + 1 && prev.x == curr.x) {
                file << "sol\n";
            } else if (prev.y == curr.y - 1 && prev.x == curr.x) {
                file << "sað\n";
            }

            
        }
    }

    file << std::endl;
    file << "\nKraliçe Karýncaya Giden En Kýsa Yol" << std::endl;

    for (int i = 0; i < path.getSize(); ++i) {
        file << "(" << path[i].x << "," << path[i].y << "-" << i + 1 << ")";
        if (i < path.getSize() - 1) {
            file << " -> ";
        }
    }

    file << std::endl;
    file << "Toplam maliyet: " << totalCost << std::endl;
    file.close();
}



int main(){
	//import the maze
	std::string filename = "Labirent.txt";
	Maze labyrinth(filename);
	
	//creat a graph
	Graph<Node> graph;
	
	//add vertices
	for(int i = 0; i< labyrinth.getRows(); i++){
		for(int j = 0; j < labyrinth.getCols(); j++){
			if(labyrinth(i, j).type != 0)				
				graph.addVertex(labyrinth(i, j));
		}
	}
	
	//define edges
	for(int i = 0; i < graph.getVertices().getSize(); i++){
		Point pi = graph.getVertices()[i].data.loc;
		for(int j = 0; j < graph.getVertices().getSize(); j++){
			Point pj = graph.getVertices()[j].data.loc;
			if(pi.areNeighbors(pj))
				graph.addEdge(i,j);
		}
	}
	
	//Shortest path according to BFS and DFS algorithms 
    Solvers s;
    Vector<Point> pathBFS;
    Vector<Point> pathDFS;
    
    pathBFS = s.withBFS(graph, *labyrinth.start, *labyrinth.end);
    pathDFS = s.withDFS(graph, *labyrinth.start, *labyrinth.end);
    
    //output operations
    
    if(pathBFS.getSize() < pathDFS.getSize())
    	savePathToFile(pathBFS,"Sonuc.txt");
    else
    	savePathToFile(pathDFS,"Sonuc.txt");
    
    std::cout << "Sonuclar Sonuc.txt dosyasina yazildi" << std::endl;

	return 0; 
	
}
