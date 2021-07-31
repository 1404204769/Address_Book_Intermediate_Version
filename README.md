Address_Book_Intermediate_Version
========================================

一个使用C++实现中级的通讯录，连接了mysql数据库，使用了SSQLS保存数据，进行了略微的数据库分层操作

经过设计类图发现，使用SSQLS宏定义的话不知道该将其定义放在那个头文件中，无论放在哪里都有可能因为头文件被引用导致宏定义重复从而报错，所以决定不适用SSQLS，直接使用自定义用户类

批量产生随机数据的运行时间（十万条数据）：
  如果输出产生的数据的具体信息但是不插入数据库：32.5s
  如果输出产生的数据的具体信息并使用单次插入数据库：432s
  如果输出产生的数据的具体信息并使用事务插入数据库：60s
  如果不输出产生的数据的具体信息并使用事务插入数据库：24s
  
