#include "sqlite3.h"
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iomanip>
#include <algorithm>
#define ga goto a
#if defined(_WIN)
#define cls system("cls")
#else
#define cls
#endif
#define line for (int ii = 0; ii < 140; ii++)cout<<"~"; cout<<endl
#define define_exit sqlite3_free(errormsg);sqlite3_close(db);exit(0);
#define fn1  (vector<vector<int>>mat, int r, int c, string name)
#define define_std_in(a) {while (!(cin>>(a))){if(std_in==5)exit(0);std_in++;cout<<"输入数据不合法，请重新输入：";cin.clear();cin.ignore(2147483647,'\n');}cin.ignore(2147483647,'\n');std_in=0;}
using namespace std; char*errormsg, **result; int choose, row, col, flag = 0, std_in = 0; sqlite3*db = 0;
int jie_cheng(int num) { int s = 1; for (int i = 1; i <= num; i++)	s *= i; return s; }
int ni_xu_shu(vector<int>arr, int len) { int n = 0;	for (int i = 0; i < len - 1; i++)for (int j = i + 1; j < len; j++)if (arr[i] > arr[j])n++; return n; }
void ni_xu_shu_calc() { a:cls;	int len; cout << "请输入你的序列的长度：";	define_std_in(len);	vector<int>mat(len); cout << "请输入你的序列以空格分隔各个数字："; for (int i = 0; i < len; i++)define_std_in(mat[i]);	cout << "\n序列的逆序数是：" << ni_xu_shu(mat, len) << "\n\n1.继续计算逆序数\n2.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:ga; case 2:return; case 0:define_exit; default:return; } }
void out_mat fn1{ int flag;	if (r % 2 != 0)flag = r / 2; else flag = r / 2 - 1; cout << endl; for (int i = 0; i < r; i++)for (int j = 0; j < c; j++) { if (i == flag&&j == 0)cout << setw(8) << name << "=┃";	else if (j == 0)cout << "         ┃"; if (j == c - 1)cout << setw(3) << mat[i][j] << " ┃" << endl; else cout << setw(3) << mat[i][j]; } }
bool query_mat_bool(string name) { string query_sql = "select * from mat where name='" + name + "'"; sqlite3_get_table(db, query_sql.c_str(), &result, &row, &col, 0);	if (col == 0) { return 1; } else return 0; }
bool query_mat(vector<vector<int>>&mat, int &r, int &c, string name) { string query_sql_string = "select * from mat where name='" + name + "'"; sqlite3_get_table(db, query_sql_string.c_str(), &result, &r, &c, 0); if (c == 0)return 1; stringstream stream; stream << result[5]; stream >> r; stream.clear(); stream << result[6]; stream >> c; stream.clear(); stringstream read(result[7]); string matrix; int i = 0, j = 0, tep_mat; mat.resize(r); while (getline(read, matrix, '#')) { mat[j].resize(c); i++; stream << matrix; stream >> tep_mat; mat[j][i - 1] = tep_mat; stream.clear(); if (i == c) { i = 0; j++; } }stream.clear(); return 0; }
#define mat_input_1 if(!query_mat_bool(name)){cout<<"\n对不起，表中已经存在这个矩阵（行列式）！\n\n1.重新输入一个名字\n0.返回上一级\n请输入你的选择：";define_std_in(choose);switch(choose){case 1:ga;case 0:return;default:return;}}
void mat_input(int n) { string name; a:cls; if (n == 0) { cout << "请输入矩阵的名字："; define_std_in(name); mat_input_1;	cout << "请输入矩阵的行数："; define_std_in(row); cout << "请输入矩阵的列数："; define_std_in(col); } else { cout << "请输入行列式的名字："; define_std_in(name); mat_input_1; cout << "请输入行列式的阶数："; define_std_in(row); col = row; }	string mat_string = "", tep_mat, r_string, c_string;	stringstream stream;	vector<vector<int>>matrix(row); for (int i = 0; i < row; i++) { matrix[i].resize(col); for (int j = 0; j < col; j++) { cout << "请输入第" << i + 1 << "行的第" << j + 1 << "个数据：";	define_std_in(matrix[i][j]); stream << matrix[i][j]; stream >> tep_mat; stream.clear(); mat_string += tep_mat + "#"; } }stream << row; stream >> r_string; stream.clear(); stream << col; stream >> c_string; stream.clear(); out_mat(matrix, row, col, name); mat_string = "insert into mat values('" + name + "'," + r_string + "," + c_string + ",'" + mat_string + "')"; sqlite3_exec(db, mat_string.c_str(), 0, 0, &errormsg); cout << "\n数据插入成功！"; cout << "\n\n1.继续输入矩阵\n2.继续输入行列式\n3.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:n = 0; ga;	case 2:n = 1; ga; case 3:return; case 0:exit(0); default:return; } }
void input_title() { a:cls; line; cout << "[[[[[[[[[[::::::        【1】行列式输入              ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【2】矩阵输入                ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【3】返回上一级              ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【0】退出                    ::::::]]]]]]]]]]]"; line;	cout << "请输入你的选择：";	define_std_in(choose); switch (choose) { case 1:mat_input(1); ga; case 2:mat_input(0); ga; case 3:return;	case 0:define_exit;	default:ga; } }
void display_mat() { cls; int r = 0, c = 0, sqlbase = 4; vector<vector<int>>mat; string name;	stringstream stream;	sqlite3_get_table(db, "select * from mat", &result, &row, &col, 0);	if (row == 0) { cout << "表中暂无数据！" << endl << endl; ga; }while (sqlbase < (row + 1)*col) { if (sqlbase % 4 == 0)name = result[sqlbase]; if (sqlbase % 4 == 1) { stream << result[sqlbase]; stream >> r; }stream.clear();	if (sqlbase % 4 == 2) { stream << result[sqlbase]; stream >> c; }stream.clear(); if (sqlbase % 4 == 3) { stringstream read(result[sqlbase]); string matrix; int i = 0, j = 0, tep_mat;	mat.resize(r);	while (getline(read, matrix, '#')) { mat[j].resize(c); i++; stream << matrix; stream >> tep_mat; mat[j][i - 1] = tep_mat; stream.clear(); if (i == c) { i = 0; j++; } }out_mat(mat, r, c, name); }sqlbase++; }a:cout << "\n1.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:return; case 0:exit(0); default:return; } }
int full_permutation(vector<vector<int>>mat, int len) { vector<int>arr(len); int sum = 0; for (int i = 0; i < len; i++)arr[i] = i; do { int result_tep = 1; for (int tep = 0; tep < len; tep++)result_tep *= mat[tep][arr[tep]]; if (ni_xu_shu(arr, len) % 2 != 0)result_tep *= -1; sum += result_tep; } while (next_permutation(arr.begin(), arr.end())); return sum; }
void mat_calc() { string name; vector<vector<int>>mat; a:cls; b:cout << "请输入需要计算的行列式的名字："; define_std_in(name); if (query_mat(mat, row, col, name)) { cout << "\n对不起，表中不存在这个矩阵（行列式）！请重新输入。\n"; goto b; } else if (row != col) { cout << "\n对不起，名字空间里存储的不是行列式！请重新输入。\n"; goto b; }out_mat(mat, row, col, name); int result_mat = full_permutation(mat, row); cout << "\n\n行列式的展开式共有" << jie_cheng(row) << "项\n行列式的结果是：" << result_mat << "\n\n"; cout << "1.继续计算\n2.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:ga; case 2:return; case 0:exit(0); default:return; } }
void save_mat fn1{ stringstream stream; string mat_string, tep_mat; for (int i = 0; i < r; i++)for (int j = 0; j < c; j++) { stream << mat[i][j]; stream >> tep_mat; stream.clear(); mat_string += tep_mat + "#"; }mat_string = "update mat set data='" + mat_string + "' where name='" + name + "'"; sqlite3_exec(db, mat_string.c_str(), 0, 0, &errormsg); cout << "保存成功！\n1.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:return; case 0:define_exit; default:return; } }
#define mat_calc_1 a:cls;out_mat(mat,r,c,name)
#define mat_calc_2 { cout << "输入的数字无效！\n1.重新输入\n2.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose){ case 1:ga; case 2:return; case 0:define_exit; default:return; } }
#define mat_calc_3 cls;out_mat(mat,r,c,name)
#define fn (mat, row, col, name);
#define define_cout(a) cout<<"请输入要"#a"的数字：";define_std_in(num);
#define mat_calc_lines_1 mat_calc_1;int new_r, num; cout << "请输入要操作的行数："; define_std_in(new_r);if (!(new_r>0 && new_r <= r))mat_calc_2
#define mat_calc_lines_2 for (int i = 0; i < r; i++)for (int j = 0; j < c; j++)if (i == new_r - 1)
#define mat_calc_lines_3 cout << "结果是：\n";out_mat(mat,r,c,name);cout<<"1.保存矩阵（行列式）\n2.返回上一级\n0.退出\n请输入你的选择：";define_std_in(choose);switch(choose){case 1:save_mat(mat,r,c,name);return;case 2:return;case 0:define_exit;default:return;}
void mat_lines_add fn1{ mat_calc_lines_1 define_cout(加) mat_calc_lines_2 mat[i][j] += num; mat_calc_lines_3; }
void mat_lines_minus fn1{ mat_calc_lines_1 define_cout(减); mat_calc_lines_2 mat[i][j] -= num; mat_calc_lines_3; }
void mat_lines_mul fn1{ mat_calc_lines_1 define_cout(乘); mat_calc_lines_2 mat[i][j] *= num; mat_calc_lines_3; }
void mat_lines_div fn1{ mat_calc_lines_1 define_cout(除); if (num == 0)mat_calc_2 mat_calc_lines_2 mat[i][j] /= num; mat_calc_lines_3; }
#define mat_calc_cols_1 mat_calc_1;int new_c, num; cout << "请输入要操作的列数："; define_std_in(new_c);if (!(new_c>0 && new_c <= c))mat_calc_2
#define mat_calc_cols_2 for (int i = 0; i < r; i++)for (int j = 0; j < c; j++)if (j == new_c - 1)
void mat_col_add fn1{ mat_calc_cols_1 define_cout(加) mat_calc_cols_2 mat[i][j] += num; mat_calc_lines_3; }
void mat_col_minus fn1{ mat_calc_cols_1 define_cout(减) mat_calc_cols_2 mat[i][j] -= num; mat_calc_lines_3; }
void mat_col_mul fn1{ mat_calc_cols_1 define_cout(乘) mat_calc_cols_2 mat[i][j] *= num; mat_calc_lines_3; }
void mat_col_div fn1{ mat_calc_cols_1 define_cout(除) mat_calc_cols_2 mat[i][j] /= num; mat_calc_lines_3; }
#define mat_calc_all_1 for (int i = 0; i < r; i++)for (int j = 0; j < c; j++)
#define mat_all_1 mat_calc_3; int num;
void mat_all_add fn1{ mat_all_1 define_cout(加); mat_calc_all_1 mat[i][j] += num; mat_calc_lines_3; }
void mat_all_minus fn1{ mat_all_1 define_cout(减); mat_calc_all_1 mat[i][j] -= num; mat_calc_lines_3; }
void mat_all_mul fn1{ mat_all_1 define_cout(乘); mat_calc_all_1 mat[i][j] *= num; mat_calc_lines_3; }
void mat_all_div fn1{ mat_calc_1; int num; define_cout(除); if (num == 0)mat_calc_2 mat_calc_all_1 mat[i][j] /= num; mat_calc_lines_3; }
#define tam_1 mat_calc_1; int r1, r2; cout << "请输入要操作的行数："; define_std_in(r1); cout << "请输入另一个行数："; define_std_in(r2);
#define tam_2 mat_calc_1; int c1, c2; cout << "请输入要操作的列数："; define_std_in(c1); cout << "请输入另一个列数："; define_std_in(c2);
#define tam_3 tam_1 if ((!(r1>0 && r1 <= r)) || (!(r2>0 && r2 <= r)))mat_calc_2
#define tam_5 for (int i = 0; i < r; i++)for (int j = 0; j < c; j++)for (int m = 0; m < r; m++)for (int n = 0; n < c; n++)
#define tam_4 tam_5 if(i==r1-1&&m==r2-1&&j==n)
#define tam_6 tam_5 if(j==c1-1&&n==c2-1&&i==m)
#define tam_7 tam_2 if ((!(c1>0 && c1 <= c)) || (!(c2>0 && c2 <= c)))mat_calc_2
void addlines_t fn1{ tam_3 tam_4	mat[i][j] += mat[m][n]; mat_calc_lines_3; }
void minuslines_t fn1{ tam_3 tam_4	mat[i][j] -= mat[m][n]; mat_calc_lines_3; }
void addcol_t fn1{ tam_7 tam_6 mat[i][j] += mat[m][n]; mat_calc_lines_3; }
void minuscol_t fn1{ tam_7 tam_6 mat[i][j] -= mat[m][n]; mat_calc_lines_3; }
#define adms1 mat_calc_3; string nname; vector<vector<int>>nmat; int ncol, nrow; b:cout << "请输入另一个矩阵的名字："; define_std_in(nname);if (query_mat(nmat, nrow, ncol, nname)){ cout << "对不起，表中不存在这个矩阵（行列式）！请重新输入。\n"; goto b; }out_mat(nmat,nrow,ncol,name);tam_5 if (i == m&&j == n)
void mat_add_t fn1{ adms1 mat[i][j] += mat[m][n]; mat_calc_lines_3; }
void mat_minus_t fn1{ adms1 mat[i][j] -= mat[m][n]; mat_calc_lines_3; }
#define mul1 cout<<"结果是：\n";out_mat(lmat,lrow,lcol,name);cout<<"1.保存矩阵（行列式）\n2.返回上一级\n0.退出\n请输入你的选择：";define_std_in(choose);switch(choose){case 1:save_mat(lmat,lrow,lcol,name);return;case 2:return;case 0:define_exit;default:return;}
#define mul2 cout<<"结果是：\n";out_mat(lmat,r,c,name);cout<<"1.保存矩阵（行列式）\n2.返回上一级\n0.退出\n请输入你的选择：";define_std_in(choose);switch(choose){case 1:save_mat(lmat,r,c,name);return;case 2:return;case 0:define_exit;default:return;}
#define mul3 for (int j = 0; j < c; j++)for (int m = 0; m < r; m++)for (int n = 0; n < c; n++)for (int x = 0; x < r; x++)for (int y = 0; y < c; y++)if (i == m&&y == j&&n == x)
void mat_mul_t fn1{ mat_calc_1; string nname; vector<vector<int>>nmat, lmat; int ncol, nrow, lcol, lrow; b:cout << "请输入另一个矩阵的名字："; define_std_in(nname); if (query_mat(nmat, nrow, ncol, nname)) { cout << "对不起，表中不存在这个矩阵（行列式）！请重新输入。\n"; goto b; }if (c != nrow) { cout << "\n对不起两个行列式不可以相乘！\n1.重新选择矩阵\n2.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:ga; case 2:return; case 0:define_exit; default:return; } }out_mat(nmat, nrow, ncol, nname); lrow = r, lcol = ncol; lmat.resize(r); for (int i = 0; i < lrow; i++) { lmat[i].resize(lcol); mul3 lmat[i][j] += mat[m][n] * nmat[x][y]; }mul1 }
void msquare fn1{ mat_calc_3; string nname; vector<vector<int>>nmat, lmat; lmat.resize(r); for (int i = 0; i < r; i++) { lmat[i].resize(c); mul3 lmat[i][j] += mat[m][n] * mat[x][y]; }mul2 }
#define chg1 {tep = mat[i][j]; mat[i][j] = mat[m][n]; mat[m][n] = tep;}
void linechange fn1{ tam_3 int tep; tam_5 if (i == r1 - 1 && m == r2 - 1 && j == n)chg1 mat_calc_lines_3; }
void colchange fn1{ tam_7 int tep; tam_5 if (j == c1 - 1 && c2 == n + 1 && i == m)chg1 mat_calc_lines_3; }
#define allcg int tep;for (int i=0;i<r;i++)for(int j=0;j<c;j++)if(i>j){tep=mat[i][j];mat[i][j]=mat[j][i];mat[j][i]=tep;}
void allchange fn1{ mat_calc_3; allcg mat_calc_lines_3; }
void allchangehx(vector<vector<int>>&mat, int r, int c) { allcg }
int bszhx(vector<vector<int>>mat, int r, int c, int i, int j) { vector<vector<int>>nmat; nmat.resize(r - 1); int y = 0; for (int m = 0; m < r; m++) { if (m > i)y = m - 1; else y = m; for (int n = 0; n < c; n++)if (m != i&&n != j)nmat[y].push_back(mat[m][n]); }if ((i + j + 2) % 2 == 0)return full_permutation(nmat, r - 1); else return-1 * full_permutation(nmat, r - 1); }
#define bsz vector<vector<int>>nmat;nmat.resize(r);for (int i = 0; i < r; i++){nmat[i].resize(c);for (int j = 0; j < c; j++){nmat[i][j] = bszhx(mat, r, c, i, j);}}mat = nmat;allchangehx(mat, r, c);
void mat_bsz fn1{ mat_calc_3; bsz mat_calc_lines_3; }
void mat_bszhx(vector<vector<int>>&mat, int r, int c) { bsz }
void out_mathx(vector<vector<double>>mat, int r, int c, string name) { int flag; if (r % 2 != 0)flag = r / 2; else flag = r / 2 - 1; cout << endl; for (int i = 0; i < r; i++)for (int j = 0; j < c; j++) { if (i == flag&&j == 0)cout << setw(8) << name << "=┃"; else if (j == 0)cout << "         ┃"; if (j == c - 1)cout << setprecision(5) << setw(5) << mat[i][j] << "┃" << endl; else cout << setprecision(5) << setw(5) << mat[i][j]; } }
void mat_ni fn1{ mat_calc_3; int f = full_permutation(mat, r); vector<vector<double>>nmat; if (f == 0) { cout << "行列式的值为零，不存在逆矩阵！\n"; ga; } mat_bszhx(mat, r, c); nmat.resize(r); for (int i = 0; i < r; i++) { nmat[i].resize(c); for (int j = 0; j < c; j++)nmat[i][j] = (double)mat[i][j] / (double)f; }cout << "结果是：\n"; out_mathx(nmat, r, c, name); a:cout << "1.返回上一级\n0.退出\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:return; case 0:define_exit; default:return; } }
#define fang if(row!=col){cout<<"不是方阵！不能实现这个功能！\n\n1.重新输入\n2.返回上一级\n0.退出\n请输入你的选择：";define_std_in(choose)switch(choose){case 1:ga;case 2:return;case 0:define_exit;}}
void mat_title() { flag = 0; string name; vector<vector<int>>mat; a:cls;	line; cout << "~~~~~~~~~~~~~~~~加法~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~减法~~~~~~~~~~~~~~~~\n======【1】两个矩阵（行列式）加    ===【7】两个矩阵（行列式）减 ============【2】矩阵（行列式）行加      ===【8】矩阵（行列式）行减   ============【3】矩阵（行列式）列加      ===【9】矩阵（行列式）列减   ============【4】矩阵（行列式）两行加    ===【10】矩阵（行列式）两行减============【5】矩阵（行列式）两列加    ===【11】矩阵（行列式）两列减============【6】矩阵（行列式）全加      ===【12】矩阵（行列式）全减  ======\n~~~~~~~~~~~~~~~~乘法~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~除法~~~~~~~~~~~~~~\n======【13】两个矩阵乘             =========================================【14】矩阵（行列式）行乘     ===【17】矩阵（行列式）行除  ============【15】矩阵（行列式）列乘     ===【18】矩阵（行列式）列除  ============【16】矩阵（行列式）全乘     ===【19】矩阵（行列式）全除  ======\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~其它~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n[[[[[[[[[[::::::        【20】矩阵平方               ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【21】矩阵行交换             ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【22】矩阵列交换             ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【23】伴随矩阵               ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【24】转置矩阵               ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【25】逆矩阵                 ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【26】返回上一级             ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::        【0】退出                    ::::::]]]]]]]]]]]\n"; line; if (flag == 0) { b:cout << "请输入需要操作的矩阵的名字："; define_std_in(name); if (query_mat(mat, row, col, name)) { cout << "对不起，表中不存在这个矩阵（行列式）！请重新输入。\n"; goto b; } }query_mat(mat, row, col, name); out_mat(mat, row, col, name); flag = 1; cout << "请输入你的选择："; define_std_in(choose); switch (choose) { case 1:mat_add_t fn ga; case 2:mat_lines_add fn ga; case 3:mat_col_add fn ga;	case 4:addlines_t fn ga;	case 5:addcol_t fn ga; case 6:mat_all_add fn ga; case 7:mat_minus_t fn ga;	case 8:mat_lines_minus fn ga; case 9:mat_col_minus fn ga; case 10:minuslines_t fn ga; case 11:minuscol_t fn ga;	case 12:mat_all_minus fn ga;	case 13:mat_mul_t fn ga; case 14:mat_lines_mul fn ga; case 15:mat_col_mul fn ga;	case 16:mat_all_mul fn ga; case 17:mat_lines_div fn ga; case 18:mat_col_div fn ga; case 19:mat_all_div fn ga;	case 20:fang msquare fn ga;	case 21:linechange fn ga; case 22:colchange fn ga; case 23:fang mat_bsz fn ga; case 24:fang allchange fn ga; case 25:fang mat_ni fn ga; case 26:return; case 0:define_exit; default:ga; } }
void mat_delete() { string name; b:cls; printf("请输入需要删除的矩阵或者行列式的名字："); define_std_in(name); string sql_string = "delete from mat where name='" + name + "'"; if (query_mat_bool(name)) { cout << "\n对不起，表中不存在这个矩阵（行列式）！\n\n"; ga; }sqlite3_exec(db, sql_string.c_str(), 0, 0, &errormsg); cout << "\n删除成功！\n\n"; a:cout << " 1.继续删除\n2.返回上一级\n0.退出\n请输入你的选择：";	define_std_in(choose); switch (choose) { case 1:goto b; case 2:return; case 0:define_exit; default:return; } }
#define update_mat_1 a:cls; cout<<"请输入需要修改的矩阵(行列式)的名字：";define_std_in(name);if(query_mat_bool(name)){cout<<"\n对不起，表中不存在这个矩阵（行列式）！\n\n";goto b;}
#define update_mat_2 cout<<"修改成功\n\n";b:cout<<"1.继续修改\n2.返回上一级\n0.退出\n请输入你的选择：";define_std_in(choose);switch(choose){case 1:ga;case 2:return;case 0:define_exit;default:return;}
void update_mat_name() { string name, name_after, sql_string; update_mat_1; cout << "矩阵(行列式)的名字修改为：";	define_std_in(name_after); sql_string = "update mat set name='" + name_after + "' where name='" + name + "'"; sqlite3_exec(db, sql_string.c_str(), 0, 0, &errormsg); update_mat_2; }
#define update_mat_3 for(int i=0;i<row;i++){mat[i].resize(col);for(int j=0;j<col;j++){cout<<"请输入第"<<i+1<<"行的第"<<j+1<<"个数据：";define_std_in(mat[i][j]);stream<<mat[i][j];stream>>tep_mat;stream.clear();mat_string+=tep_mat+"#";}}mat_string="update mat set data='"+mat_string+"' where name='"+name+"'";sqlite3_exec(db,mat_string.c_str(),0,0,&errormsg);
void update_mat_con() { string name, tep_mat, mat_string; stringstream stream; vector<vector<int>>mat; update_mat_1;	cout << "这是一个" << row << "行" << col << "列的矩阵(行列式)。\n"; cout << "是否修改矩阵(行列式)的行列数（1 / 0）："; define_std_in(flag);	if (flag == 1) { cout << "请输入修改后的行数："; define_std_in(row);	cout << "请输入修改后的列数："; define_std_in(col); mat.resize(row);	update_mat_3; stream << row; stream >> mat_string; stream.clear(); mat_string = "update mat set lines=" + mat_string + " where name='" + name + "'"; sqlite3_exec(db, mat_string.c_str(), 0, 0, &errormsg); stream << col; stream >> mat_string; stream.clear(); mat_string = "update mat set cols=" + mat_string + " where name='" + name + "'"; sqlite3_exec(db, mat_string.c_str(), 0, 0, &errormsg); } else { update_mat_3; }out_mat(mat, row, col, name); update_mat_2; }
void update_mat_title() { a:cls; line; cout << "[[[[[[[[[[::::::      【1】修改矩阵(行列式)的名字    ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【2】修改矩阵(行列式)数据      ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【3】返回上一级                ::::::]]]]]]]]]]]" << "[[[[[[[[[[::::::      【0】退出                      ::::::]]]]]]]]]]]"; line; cout << "\n\n请输入你的选择："; define_std_in(choose); switch (choose) { case 1:update_mat_name(); ga; case 2:update_mat_con(); ga; case 0:define_exit; default:return; } }
void welcome() { a:cls; line; cout << "\t\t\t矩阵--Matlab 模拟系统\n\n\n"; line; cout << "[[[[[[[[[[::::::      【1】输入矩阵（行列式）        ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【2】输出矩阵（行列式）        ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【3】修改矩阵（行列式）        ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【4】删除矩阵（行列式）        ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【5】计算逆序数                ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【6】行列式求值                ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【7】矩阵（行列式）的基本运算  ::::::]]]]]]]]]]]\n[[[[[[[[[[::::::      【0】退出                      ::::::]]]]]]]]]]]\n"; line; cout << "请输入你的选择：";	define_std_in(choose); switch (choose) { case 1:input_title(); ga; case 2:display_mat(); ga; case 3:update_mat_title(); ga; case 4:mat_delete(); ga; case 5:ni_xu_shu_calc(); ga; case 6:mat_calc(); ga; case 7:mat_title(); ga; case 0:define_exit; default:ga; } }
int main() { 
    std::string create_table = "create table mat(name text primary key,lines integer,cols integer,data text)"; 
    sqlite3_open("./matrix.db", &db);
    sqlite3_exec(db, create_table.c_str(), 0, 0, &errormsg);
#if defined(_WIN)
system("mode con cols=70 lines=50");	system("title 矩阵--Matlab 模拟系统"); system("color 3e");
#endif
    welcome(); sqlite3_free(errormsg);
    sqlite3_close(db); return 0; 
}
