General Architecture info: 
- a search engine for a large collection of financial news articles from Jan - May 2018.  
- The dataset contains more than 300,000 articles
- search engine will take a query and find the documents that satisfy the request
- Main components:
 
  Index Handler 
    * Read and write to the main word index 
    * Create inverted file index to store references from each element to be indexed to the 
      corresponding document(s) in which those elements exist
    * Create and maintain an index of ORGANIZATION entities and an index of PERSON entities (store each inside an AVL Tree) 
    * Searches the inverted file index based on a request from the query processor
  
  Document parser/processor (RapidJson parser)
    * stems words & removes stop words from read in news articles 
  
  Query processor
    * Handles user entered phrases by deliniating by boolean & ORG/PERSON
    * EX: AND year fender (finds documents with year and fender) 
    * EX: AND year fender PERSON daniel wallis (finds documents that contain year, fender, and daniel wallis) 
 

##Run

`/Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake --build "/Users/maxlink/Desktop/DS SE test run/search-engine-main/cmake-build-debug" --target 22su_search_engine`

 
6/22/22 

worked on program terminal userInterface 
worked on parsing words from documents

references:
* stopwords list from https://gist.github.com/larsyencken/1440509
* stringstream string splitting:https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/


6/23/22
* AVL test code
* json parsing
* code for `rapidjson` filesystem readin https://rapidjson.org/md_doc_stream.html

6/24/22
* created templated avl tree class with reference from 

6/25/22
* created search function for AVL tree templated class 
* worked on stemming words
