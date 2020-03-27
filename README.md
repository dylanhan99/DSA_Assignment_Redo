# DSA_Assignment_Redo
Second attempt of DSA assignment. 
Reasons for redoing:
- First attempt was rather disappointing
- To practise better programming habits
- Familiarisation of C++

Things that could be improved:
1. Making smaller functions. This would improve the reusability of many functions.
   E.g. In the graph class, the function displayLines() to view all line prefixes could be shortened 
        so that it ONLY displays the lines, as this feature is used multiple times in other features
        as well. The parts where it asks for user input should be handled outside of the function.
       
2. Using better search algorithms over iterative search (E.g. Binary).
   E.g. Currently, where the programme needs to search search for a StationID in a line of Routes.csv,
        it does an iterative search to look for any StationID. As there are many instances of nested
        loops throughout the programme, introducing a better search algorithm would greatly reduce the
        amount of time it takes for functions to complete.
