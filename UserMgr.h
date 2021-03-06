#pragma once
#ifndef _USERMGR_H_
#define _USERMGR_H_
#include<vector>
#include "User.h"
#include "DB.h"
#include <windows.h>
#include <mysql++.h>
#define TelNum 11 /*电话的位数*/
//50个   0-49，百家姓
constexpr int nCharSize = 20;/*字符串大小*/
constexpr int nTelSize = 40;/*电话开头的种类*/
constexpr int nNameSize = 50;/*2021最受欢迎的男孩女孩名字各50个*/
constexpr int nProvinceSize = 53;/*26个省份，大写字母给每个省分区(按现实划分太麻烦)*/
constexpr int nAreaSize = 34;/*我国共有34个省级行政区域，包括23个省，5个自治区，4个直辖市，2个特别行政区。*/

const char caLastName[nNameSize][nCharSize] = { "赵","钱","孙","李","周","吴","郑","王","冯","陈",
								"褚","卫","蒋","沈","韩","杨","朱","秦","尤","许",
								"何","吕","施","张","孔","曹","严","华","金","魏",
								"陶","姜","戚","谢","邹","喻","柏","水","窦","章",
								"云","苏","潘","葛","奚","范","彭","郎","鲁","韦" };
const char caWomanName[nNameSize][nCharSize] = { "晓悦","水静","葱娟","晓迪","绿芸","安蕾","松铃","秋娇","雅可","虹媛",
									"寒菊","梓燕","映茹","成美","姝妍","芬霏","梦清","蓉洁","慕梅","诗琪",
									"倩冰","闻霜","菲凤","华琪","桃蓝","嘉莉","晓花","志丽","雅绿","柯洁",
									"莲璐","水月","春雁","依青","夕穗","菲玉","雪春","佩兰","淑琳","月婵",
									"娅清","冰玉","芳菲","正妍","苡彤","婧雯","曼玲","芳辰","韶涵","兰春" };
const char caManName[nNameSize][nCharSize] = { "俊彤","鸿范","嘉瑜","乐科","哲佩","宝彦","栎滨","元宇","学萸","月恺",
									"佳晔","嘉柯","凯西","英安","继逸","鸿林","光楠","锐晖","运福","弘怀",
									"茂华","承博","海才","鸿培","明国","鹏澄","文轩","煜涵","睿康","星洲",
									"佳昂","建桥","宏宇","梓德","坚泽","奇生","新言","乐然","景慕","宏仪",
									"建茗","胤鹏","博飞","宏霁","伟莎","宇羲","嘉勋","文宁","高蓬","兴赫" };
const char caDistrict_Name[nProvinceSize][nCharSize] = { "A区","B区","C区","D区","E区",
							 "F区","G区","H区","I区","J区",
							 "K区","L区","M区","N区","O区",
							 "P区","Q区","R区","S区","T区",
							 "U区","V区","W区","X区","Y区","Z区" };
const char caProvincial_Name[nAreaSize][nCharSize] = { "北京市","天津市","上海市","重庆市","河北省",
						   "山西省","辽宁省","吉林省" ,"黑龙江省","江苏省",
						   "浙江省","安徽省","福建省","江西省","山东省",
						   "河南省","湖北省","湖南省","广东省","海南省",
						   "四川省","贵州省","云南省","陕西省","甘肃省",
						   "青海省","台湾省","内蒙古自治区","广西壮族自治区","西藏自治区",
						   "宁夏回族自治区","新疆维吾尔自治区","香港特别行政区","澳门特别行政区" };
//中国电信+中国卫通  手机号码开头数字 133、142、144、146、148、149、153、180、181、189
//中国联通+中国网通  手机号码开头数字 130、131、132、141、143、145、155、156、185、186
//中国移动+中国铁通  手机号码开头数字 134、135、136、137、138、139、140、147、150、151、152、157、158、159、182、183、187、188
//总结：范围在130~159  180~189
const char caTelHead[nTelSize][nCharSize] = { "130","131","132","133","134","135","136","137","138","139",
						   "140","141","142","143","144","145","146","147","148","149",
						   "150","151","152","153","154","155","156","157","158","159",
						   "180","181","182","183","184","185","186","187","188","189" };

class CUserMgr {
public://内部的逻辑函数
	CUserMgr();
	~CUserMgr();
	bool CreateUser(CUser& user,CDB& db);/*新建一个CUser，具体数据函数内从命令行获取*/
	bool AddUser( CDB& db);/*用于将数据添加到addr_book数据库中*/
	bool ProductUser(CDB& db,int num);/*用于产生指定数量的随机数据*/
	bool Show(const mysqlpp::Query& query);/*对数据输出的功能进行封装*/
	bool ShowOne(CDB& db);/*根据名字展示数据*/
	bool ShowAllName(CDB& db);//打印输出所有的现存的名字
	void RandUser(CDB& db, CUser& user);/*用于生成随机数据*/
	void SetSrand();/*修改随机步长*/
	int RandNum(int nval);/*获取随机数*/
	std::string RandTel();/*随机产生电话*/
	std::string RandName();/*随机产生名字*/
	std::string RandAddr();/*随机产生地址*/
	bool CheckTel(const std::string& strTel, CDB& db);/*用于检查手机号是否规范，并且判断是否存在重复手机号*/
	void VecFree();/*释放vector数组内的所有指针数据*/
private:
	std::vector<CUser*>m_vecUser;//使用vector数组来管理所有的CUser对象
};
#endif // !_USERMGR_H_

