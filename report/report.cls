\documentclass{adsrprt}


% change this: (do NOT add your name, only your s-number!)
\newcommand\snumA{s5885671}        % student number 1
\newcommand\snumB{s5962021}        % student number 2
\newcommand\assgnnum{5}            % assignment number
\newcommand\assgntitle{Maze}  % assignment title

% do not change this:
\title{Assignment \assgnnum:``Maze''\\Programming report}
\subtitle{\snumA\ and \snumB\\Algorithms and Data Structures in C (2024-2025)}
\headertitle{Assignment \assgnnum: ``\assgntitle''}
\headersubtitle{Report by \snumA\ and \snumB}


\begin{document}
\maketitle

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% NOTE: You MUST read and follow Appendix E of the lecture notes! %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

\section*{Problem description}

\textbf{General:} \\
The goal is to write a C program that finds the shortest path through a special type of maze called the \emph{Inverto-Maze}. This maze consists of chambers connected by one-way tunnels. Some chambers contain a special button (we will henceforth denote the button as \texttt{REV}) that, when pressed, reverses the direction of all tunnels in the maze.

The program should compute the shortest path from the entrance (chamber 1) to the exit (chamber $n$), taking into account any reversals caused by pressing these buttons.

\textbf{Input and output behavior:} \\
The input begins with two integers: the number of chambers $n$ and the number of tunnels $m$. This is followed by a list of chambers that have a reverse (\texttt{REV}) -button, ending with \texttt{-1}. Then come $m$ lines, each containing three integers: the starting chamber $a$, the destination chamber $b$, and the length $\ell$ of the tunnel from $a$ to $b$. All tunnels are initially one-way from $a$ to $b$.

The output starts with the total length of the shortest path from chamber 1 to chamber $n$. Then, the sequence of chambers along the path is printed, one per line. If a button is pressed in a chamber, an \texttt{R} is printed after its number. The final chamber (chamber $n$) is never followed by an \texttt{R}. If no path exists from chamber 1 to $n$, the output should be \texttt{IMPOSSIBLE}.


\section{Problem analysis}

% The following example illustrates how to typeset pseudocode:


To solve the Inverto-Maze problem, we use a version of Dijkstra’s algorithm that keeps track of two possible states for each chamber: normal and inverted. These states reflect the current direction of the maze’s tunnels. If a chamber includes a reverse button, the algorithm lets you switch between normal and inverted states while passing through, without adding to the total path length.

The algorithm uses two separate graphs—one for each state—and uses a min-heap priority queue to pick the next chamber. At each step, it checks the current chamber and its state to determine which tunnels is can pick. It updates distances only when it finds a shorter path. In the end, it compares the shortest distances to the exit chamber from both states and picks the smaller one.

\begin{tabbing}
xxx \= xxx \= xxx \= xxx \= \kill
\Algorithm~ModifiedDijkstra(maze, invertedMaze) \\
\> \Input: original and reversed maze graphs \\
\> \Result: shortest path from chamber 1 to chamber n \\[0.5em]

\> \Let~$n$ \becomes~number of chambers in maze \\
\> \Let~dist[c][s] \becomes~infinity for all chambers $c$ and states $s$ \\
\> \Let~dist[1][0] \becomes~0 \Comment{start from chamber 1 in normal state} \\
\> \Let~heap \becomes~an empty min-heap \\
\> insert (1, 0, 0) into heap \Comment{(chamber, state, distance)} \\[0.5em]

\> \While~heap is not empty \\
\> \> (c, s, d) \becomes~pop from heap \\
\> \> \If~(c, s) already visited \Then~\textbf{continue} \\
\> \> mark (c, s) as visited \\[0.5em]

\> \> \If~s = 0 \Then~edges \becomes~maze.tunnels[c] \\
\> \> \Else~edges \becomes~invertedMaze.tunnels[c] \\[0.5em]

\> \> \While~edges not null \\
\> \> \> neighbor \becomes~edges.to \\
\> \> \> newDist \becomes~d + edges.weight \\
\> \> \> \If~newDist $<$ dist[neighbor][s] \Then \\
\> \> \> \> dist[neighbor][s] \becomes~newDist \\
\> \> \> \> prev[neighbor][s] \becomes~(c, s) \\
\> \> \> \> insert (neighbor, s, newDist) into heap \\
\> \> edges \becomes~edges.next \\[0.5em]

\> \> \If~chamber c has a reverse button \Then \\
\> \> \> switchedTo \becomes~1 - s  \Comment{the opposite state of the current chamber} \\
\> \> \> \If~d $<$ dist[c][flipped] \Then \\
\> \> \> \> dist[c][flipped] \becomes~d \\
\> \> \> \> prev[c][flipped] \becomes~(c, s) \\
\> \> \> \> insert (c, flipped, d) into heap \\[0.5em]

\> \Let~exitDist \becomes~minimum of dist[n][0] and dist[n][1] \\
\> \If~exitDist = infinity \Then~print IMPOSSIBLE \\
\> \Else~print exitDist and backtrack path from corresponding state
\end{tabbing}


\section{Program design}


We define helper functions in a number of files for input reading, heap operations, and graph representation. The program uses a custom \texttt{Heap} data structure as a priority queue for Dijkstra's algorithm, and a \texttt{Maze} data structure to represent both the normal and inverted tunnel graphs. Each chamber is represented by a \texttt{Chamber} struct, and the algorithm maintains progress using \texttt{NodeState} structs, which hold the current state (normal or inverted), distance, and information for backtracking.

The main logic is implemented in the function \texttt{findShortestPath}. It starts by initializing all node states (both normal and reversed versions of the maze), as well as a \texttt{visited} table and a heap. The algorithm runs a variation of Dijkstra’s algorithm, considering each chamber in both of its states. In every step, the algorithm pops the node with the shortest discovered distance from the heap and explores its outgoing tunnels from either the original or reversed graph, depending on the state. If a chamber has a reverse button, the state can be flipped without contributing to the total path length.

The \texttt{main.c} program inputs the input maze through \texttt{readInput}, constructs its inverted version through \texttt{invertMaze}, and then calls \texttt{findShortestPath} to compute the shortest path to exit. Both versions of the maze are then deallocated.


\paragraph*{Design choice.}
Instead of reversing the maze on demand, i.e whenever the reverse button is present, we decided to construct the reverse maze once in advance. This avoids costly graph operations in the middle of path-finding and also simplifies state-flipping logic in the middle of traversal. The state (normal or reversed) of each chamber is assigned its own node in the algorithm, allowing us to separate reverse and normal logic handling and allows easier heap management. This framework also aligns well with the structure of Dijkstra's algorithm, which can be generalized fairly naturally to multi-state systems.

\paragraph*{Time complexity.}
Let $n$ be the number of chambers and $m$ the number of tunnels. Since each chamber has two states, the graph effectively has $2n$ nodes. For each connection in the maze, the algorithm checks (at most once per state) whether it leads to a shorter path to the next chamber. This results in at most \texttt{O(m)} such checks across the entire maze. Insertions and removals from the heap (which contains up to $2n$ nodes) take $\mathcal{O}(\log n)$ time. Therefore, the total time complexity of the algorithm is $\mathcal{O}(m \log n)$.


\section{Evaluation of the program}

We tested the program using the input file \texttt{3.in}, which contains the following input:

\begin{verbatim}
17 20
1 7 14 10 -1
2 1 11
2 11 4
3 2 8
4 3 1
5 4 7
6 5 5
7 6 23
7 8 2
9 8 9
9 17 0
11 12 7
12 13 4
13 14 5
14 15 2
15 14 10
15 16 3
16 10 10
16 15 1
10 16 3
10 9 0
\end{verbatim}

This input describes a maze with 17 chambers and 20 tunnels. Chambers 1, 7, 14, and 10 are equipped with reverse buttons. The maze includes multiple paths, cycles, and sections where reversal of tunnel directions is essential to progress.

The output produced by the program for this input was:

\begin{verbatim}
133
1 R
2
3
4
5
6
7 R
6
5
4
3
2
11
12
13
14 R
15
16
10 R
9
17
\end{verbatim}

This output indicates that the shortest path from chamber~1 to chamber~17 has a total length of 133. 

This result is correct. Pressing the reverse buttons is needed to go back through earlier chambers or reach places that can’t be accessed otherwise. The order of chambers and the total distance match what we would expect based on how the maze is built.

We apply valgrind to check for any memory leaks with the same input. Valrind reports the following.

\begin{verbatim}
==41654== HEAP SUMMARY:
==41654==     in use at exit: 0 bytes in 0 blocks
==41654==   total heap usage: 162 allocs, 162 frees, 11,136 bytes allocated
==41654== 
==41654== All heap blocks were freed -- no leaks are possible
==41654== 
==41654== For lists of detected and suppressed errors, rerun with: -s
==41654== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
\end{verbatim}


No memory leaks are found.

Therefore, we conclude that the program correctly finds the shortest path and handles tunnel direction reversals as intended.



% \section{Extension of the program} % Optional
%
% ...

\section{Process description}

We used a modified version of Dijkstra’s algorithm as the basis of our solution, one that was altered to support the Inverto-Maze’s unique mechanic of tunnel direction inversions. It was found to be efficient to depict each room in two states—\\textit{normal} and \\textit{inverted}—and treat these as distinct nodes during the calculation of the shortest path. This two-state depiction formed the fundamental structure of the \\texttt{findShortestPath} function.

In order to handle transitions between states, we created a reversed duplicate of the maze in advance, instead of reversing the directions of the tunnels on the fly while searching. This allowed us to focus on the logic in the main loop for determining which version of the maze to search in depending on the current state. When we encountered a reverse button, we conditionally pushed the other state onto the heap conditionally without advancing the path length.

During development, we faced several technical challenges. One of them was refactoring the code to keep responsibilities separated across multiple files, such as keeping heap operations in \texttt{Heap.c} and maze-related logic in \texttt{Maze.c}. Managing multiple custom structs at once—like \texttt{Chamber}, \texttt{NodeState}, \texttt{Tunnel}, and \texttt{Maze}—was sometimes complex, especially when passing pointers between functions. Debugging memory issues and using tools like \texttt{valgrind} to detect and fix leaks was also a significant part of our workflow.

By working on this project, we learned how to extend classical algorithms like Dijkstra’s to more complex, state-based problems. We also became more confident in managing memory and struct-based data in C, and gained practical experience with modular design and debugging across multiple source files.


\section{Conclusions}

The program solves the problem of finding the shortest path through the Inverto-Maze by extending Dijkstra’s algorithm to handle dynamic tunnel reversals. It does so in a clean and effective way by treating each chamber-state combination as a distinct node. The program is efficient; its time complexity is bounded by $\mathcal{O}(m \log n)$, which is suitable given the need to explore multiple states per chamber.


\section{Appendix: program text}

We only include the \texttt{helpers.c} file in the report, as it contains the main logic of the program and implements the modified Dijkstra’s algorithm used to solve the problem.

% Here you should include the program text.
% Do NOT use screenshots or similar methods.
% Below you can see how to use \lstinputlisting{}.

\texttt{\bfseries helpers.c}
\lstinputlisting{helpers.c}

% \section{Appendix: test cases} % Optional
%
% ...

% \section{Appendix: Extensions} % Optional
%
% ...

\end{document}
