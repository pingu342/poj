* index
	* 番号を配列のindexとして使用
	* メモリを食う割にはqsortより遅い
* qsort
	* 番号リストを読み終えた後にqsort
	* indexよりも高速かつ省メモリ

| 手法 | ソースコード | Time | Memory |
|:---:|:---:|:---:|:---:|
|index|main_001|688MS|39564K|
|qsort|main_002|516MS|776K|

