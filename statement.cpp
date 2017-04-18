#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <map>
using namespace std;
struct problem
{int tl,ml; string tit,des,inp,oup,sin,sout,hint;};
string readfile(string fi)
{
	ifstream p(fi.c_str());
	string r,a;
	while(getline(p,r)) a=a+r+"\n";
	return a;
}
string qsp(string s)
{
    for(int _=1;_<=2;_++)
    {
        while(s.size()&&(s[s.size()-1]==' '||s[s.size()-1]=='\r'
        ||s[s.size()-1]=='\n'||s[s.size()-1]=='\t')) s.erase(s.end()-1);
        reverse(s.begin(),s.end());
    }
    return s;
}
string replaceall(string a,string s,string t)
{
    int p;
    while((p=a.find(s))!=-1)
        a.replace(p,s.size(),t);
    return a;
}
string beau(string s)
{
    s=replaceall(s,"&nbsp;"," ");
    int fp=0,dn=0;
    for(int i=0;i<s.size();i++)
    {
        if(s[i]=='<')
        {
            dn=1; fp=i;
            while(s[i]!='>') ++dn,++i;
            string tmp=s.substr(fp,fp+dn);
            if(tmp.substr(0,4)=="<img") continue;
            s.erase(s.begin()+fp,s.begin()+fp+dn);
            i=fp-1;
        }
    }
    return qsp(s);
}
string qz(string s)
{
    stringstream r; r<<s;
    string t,a;
    while(getline(r,t))
    {
        string tm=qsp(t);
        if(tm.size()) a=a+tm+"\n";
    }
    return a;
}
problem extract(int pid)
{
	stringstream s; s<<"bzojch-master\\p\\"<<pid<<".html";
	string r; s>>r; string ct=readfile(r);
	int st=ct.find("<main class"),et=ct.find("</main>");
	string mid=ct.substr(st,et-st);
	int h1=mid.find("<h1 "),ed=mid.find("</div>");
	string head=qsp(mid.substr(h1,ed-h1));
	string title=qsp(head.substr(30,head.find("</h1>")-30));
	int p1=head.find("<p>")+18,p2=head.find("</p>");
	string tm=head.substr(p1,p2-p1);
	int g=tm.find("s");
	string ti=tm.substr(0,g);
	int g2=g+48;
	string nx=tm.substr(g2,tm.size()-g2-2);
	problem rs; rs.tl=atoi(ti.c_str());
	rs.ml=atoi(nx.c_str()); rs.tit=title;
	int ps=mid.find("card-inner");
	p2=mid.find("</section>",ps);
	nx=mid.substr(ps,p2-ps);
	int pv=0,cur;
	map<string,string> ms;
	while((cur=mid.find("<h3>",pv)))
	{
        int ed=(cur!=-1)?cur:mid.size()-1;
        string c=mid.substr(pv+3,cur-pv);
        int fp=c.find("</h3>");
        if(fp!=-1)
        {
        string a=c.substr(0,fp); fp+=5;
        string b=c.substr(fp,c.size()-fp-1);
        int s=b.find("<hr/>");
        if(s!=-1) b=b.substr(0,s);
        else b=b.substr(0,b.size()-99);
        ms[a]=beau(b);
        }
        if(cur==-1) break;
        pv=cur+1;
	}
	rs.des=ms["题目描述"];
	rs.inp=ms["输入格式"];
	rs.oup=ms["输出格式"];
	rs.sin=qz(ms["样例输入"]);
	rs.sout=qz(ms["样例输出"]);
	rs.hint=ms["提示"];
	return rs;
}
string py(string s)
{
    stringstream r; r<<s;
    string p,a;
    while(getline(r,p)) a=a+p+"\n\n";
    return a;
}
string tostr(stringstream& r)
{
    string p,a;
    while(getline(r,p)) a=a+p+"\n";
    return a;
}
string touoj(problem p)
{
    stringstream cc;
	cc<<p.tit<<"\nTL:"<<p.tl<<"s ML:"<<p.ml<<"MB\n";
	cc<<"####题目描述\n"<<py(p.des)<<"\n";
	cc<<"####输入格式\n"<<py(p.inp)<<"\n";
	cc<<"####输出格式\n"<<py(p.oup)<<"\n";
	cc<<"####样例输入\n```\n"<<p.sin<<"```\n";
	cc<<"####样例输出\n```\n"<<p.sout<<"```\n";
	cc<<"####提示\n"<<py(p.hint)<<"\n";
	return tostr(cc);
}
int main()
{
    freopen("test.txt","w",stdout);
    //cout<<"<meta charset=\"UTF-8\">\n";
    int id; cin>>id;
	problem p=extract(id);
	cout<<touoj(p)<<"\n";
}
