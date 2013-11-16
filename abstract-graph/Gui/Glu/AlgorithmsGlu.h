/**
 * Application: AbstractGraph
 * Module: GUI
 * File: Glu/AlgorithmsGlu.h
 * Description: Glue interface for algorithms library
 *    and the GUI application
 *
 * @author Dennis J. McWherter, Jr.
 * @version $Id: AlgorithmsGlu.h 112 2012-04-29 16:52:48Z Dennis.McWherter@gmail.com $
 */

#ifndef GLU_ALGORITHMSGLU_H__
#define GLU_ALGORITHMSGLU_H__

#include "Algorithms.h"

// GraphiX Library
#include "graphix.h"

// AbstractGraph Library
#include "AGRAPHLIB.h"

#include <map>
#include <utility>

class GLWindow;

class AlgorithmsGlu
{
public:
  /**
   * Constructor
   *
   * @param scene     The scene object to manipulate
   * @param parent    The parent widget to operate on
   * @param directed  Directed or undirected graph (default = false)
   */
  AlgorithmsGlu(GRAPHIX::Scene& scene, GLWindow* parent, bool directed = false);
  
  /**
   * Destructor
   */
  virtual ~AlgorithmsGlu();
  
  /**
   * Assignment operator
   */
  AlgorithmsGlu& operator=(const AlgorithmsGlu& rhs);
  
  /**
   * Handle an action from GraphiX click handling
   *
   * @param action    The action which took place
   */
  virtual void handleAction(GRAPHIX::ACTION action);
  
  /**
   * Add a node
   *
   * @return  The node's id
   */
  virtual int addNode();
  
  /**
   * Add an edge
   *
   * @param n1      First node's id
   * @param n2      Second node's id
   * @param weight  The edge weight (default = 1)
   *
   * @return  Edge id
   */
  virtual int addEdge(int n1, int n2, int weight = 1);
  
  /**
   * Update edge weights for selected edges
   *
   * @param weight  New weight
   */
  virtual void updateEdgeWeight(int weight);
  
  /**
   * Remove selected components
   */
  virtual void removeSelected();
  
  /**
   * Run the specified algorithm
   *
   * @param alg   The algorithm to be run
   *
   * @return  Result of the algorithm. < 0 on error
   */
  virtual int runAlgorithm(ALGORITHMS alg);

protected:
  /**
   * Run the shortest path algorithm
   *
   * @return  The total weight of the shortest path. < 0 on error
   */
  virtual int algorithmShortestPath();
  
  /**
   * Run the MST algorithm
   *
   * @return  Return total weight of MST edges if G is 
   *    connected. Error if < 0
   */
  virtual int algorithmMST();
  
  /**
   * Maximum Matching
   *
   * @return  Size of max matching
   */
  virtual int algorithmMaxMatch();
  
  /**
   * Maximum network flow
   *
   * @return  Maximum flow
   */
  virtual int algorithmMaxNet();
  
  /**
   * Bipartite sets
   *
   * @return  1 if graph bipartite, 0 otherwise.
   */
  virtual int algorithmBipartite();
  
  /**
   * Odd Cycle detection
   *
   * @return  Length of odd cycle. Otherwise 0 if none exists
   */
  virtual int algorithmOddCycle();
  
  /**
   * Euler's circuit
   *
   * @return  True if path exists between source/dest. False
   *    otherwise
   */
  virtual int algorithmEulerCircuit();
  
  /**
   * Export prufer code
   *
   * @return  True if tree, false otherwise
   */
  virtual int algorithmExportPrufer();
  
  /**
   * Import prufer code
   *
   * @return  1 if good false otherwise
   */
  virtual int algorithmImportPrufer();
  
  /**
   * SCC
   *
   * @return  1 on success
   */
  virtual int algorithmSCC();
  
  /**
   * Graphic Sequence algorithm
   *
   * @return  1 on success
   */
  virtual int algorithmGraphicSequence();
  
  /**
   * Run the all pairs algorithm
   *
   * @return 1
   */
  virtual int algorithmAllPairs();
  
private:
  /**
   * Highlight a path based on vector
   *
   * @param path  A reference to a vector with path ids
   * @param color Path highlight color (default = RED)
   */
  virtual void highlightPath(const std::vector<int>& path, Color color = Color(255.0, 0.0, 0.0, 0.0));
  
  /**
   * Highlight a node list
   *
   * @param path  A reference to a vector with node ids
   * @param color Path highlight color (default = RED)
   */
  virtual void highlightNodes(const std::vector<int>& nodes, Color color = Color(255.0, 0.0, 0.0, 0.0));
  
  /**
   * Return an undirected graph if graph undirected
   *
   * @return  Undirected graph. NULL if graph directed.
   */
  virtual Graph* getUndirected() const;
  
  /**
   * Arrange nodes in a bipartite fashion
   *
   * @param setX  Left set of nodes
   * @param setY  Right set of nodes
   */
  virtual void bipartiteArrange(const std::vector<int>& setX, const std::vector<int>& setY) const;
  
  /**
   * Return a directed graph if graph directed
   *
   * @return  Directed graph. NULL if graph undirected.
   */
  virtual DiGraph* getDirected() const;
  
  /**
   * Convert string to vector
   *
   * @param str   Input string
   * @param code  The populated vector
   */
  static void stringToVector(const QString& str, std::vector<int>& code);
  
  /**
   * Build the scene from the internal graph
   */
  virtual void buildSceneFromGraph();
  
  /**
   * Build color map
   *
   * @param map    The map to build the colors on
   * @param colors Number of colors to generate
   */
  virtual void buildColorMap(std::vector<Color>& map, int colors);
  
  GRAPHIX::Scene& scene;
  GLWindow* parent;
  AbstractGraph* graph;
  std::map<std::pair<int,int>, int> allPairs, pairDist;
};

#endif /* GLU_ALGORITHMSGLU_H__ */

