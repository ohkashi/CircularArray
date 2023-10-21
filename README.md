# CircularArray
Double Buffered Circular Array

[![Licence](https://img.shields.io/badge/license-MIT-blue.svg?style=flat)](LICENSE)

## [CircularArrayDemo](CircularArrayDemo.cpp)
```
std::vector: size = 26, back = 'a': elapsed time: 630 ms.
data: b c d e f g h i j k l m n o p q r s t u v w x y z a
string: 'bcdefghijklmnopqrstuvwxyza'

std::deque: size = 26, back = 'a': elapsed time: 308 ms.
data: b c d e f g h i j k l m n o p q r s t u v w x y z a
string: 'bcdef?E?

CircularArray: size = 26, Tail = 'a': elapsed time: 195 ms.
data: b c d e f g h i j k l m n o p q r s t u v w x y z a
string: 'bcdefghijklmnopqrstuvwxyza'

----------------------------------------------------------------------

std::deque: size = 32, back = 'E': elapsed time: 241 ms.
data: F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` A B C D E
string: 'FGH?혨??ko-KR'

jnk0le::Ringbuffer: size = 32, Tail = 'E': elapsed time: 205 ms.
data: F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` A B C D E
string: 'FGHIJKLMNOPQRSTUVWXYZ[\]^_`감?⸮'

CircularArray: size = 32, Tail = 'E': elapsed time: 170 ms.
data: F G H I J K L M N O P Q R S T U V W X Y Z [ \ ] ^ _ ` A B C D E
string: 'FGHIJKLMNOPQRSTUVWXYZ[\]^_`ABCDE'

Press any key to test thread-safe.
```
