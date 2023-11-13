# file_Compression

Huffman Algorithm is an efficient way for file Compression and Decompression. This program exactly follows huffman algorithm. It reads frequent characters from input file and replace it with shorter binary codeword. The original file can be produced again without loosing any bit.

# How To Use

Compression:
  	./encode <file to .compress>

Decompression:
    	./decode <file to .uncompress>

# Example:

Text: aabcbaab
  
| Content | Comment                          |
| ------- | -------------------------------- |
| 3       | N=3 (a,b,c)                      |
| a   "1" |  character and corresponding code "1" |
| b  "01" |  character and corresponding code "01" |
| c  "00" |  character and corresponding code "00" |
| 4       | Padding count                    |
| [0000]  | Padding 4 zeroes                 |
| [1] [1] [01] [00] [01] [1] [1] [01] | Actual data, code in place of char |

