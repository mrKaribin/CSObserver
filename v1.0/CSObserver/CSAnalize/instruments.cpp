#include "instruments.h"


void WebPageQueue::addPage(QWebEnginePage *page, QString url)
{
    pages << page;
    urls << url;
    if(!loading) nextPage();
}

void WebPageQueue::nextPage()
{
    if(loading == true)
    {
        disconnect(pages.first(),&QWebEnginePage::loadFinished,this,&WebPageQueue::nextPage);
        disconnect(pages.first(),&QWebEnginePage::destroyed,this,&WebPageQueue::nextPage);
        pages.remove(0);
        urls.remove(0);
    }
    if(pages.size()==0) {loading = false; return;}
    connect(pages.first(),&QWebEnginePage::loadFinished,this,&WebPageQueue::nextPage);
    connect(pages.first(),&QWebEnginePage::destroyed,this,&WebPageQueue::nextPage);
    pages.first()->load(QUrl(urls.first()));
    loading = true;
}


HtmlParse::HtmlParse()
{

}

QString HtmlParse::cutBetween(QString html, QString start, QString finish)
{
    QString result="empty";

    int a = html.indexOf(start);
    if(a==-1) return result;

    int b = html.indexOf(finish);
    if(b==-1) return result;

    result = html.mid(a,b-a);

    return result;
}

QString HtmlParse::cutAfter(QString html, QString findIt)
{
    QString result="empty";

    int k = html.indexOf(findIt); int j;

    if(k==-1) return result;
    else
    {
        k += findIt.size();
        j = findEnd(html,k,html.size(),1);
    }

    if(j!=-1)result = html.mid(k,j);

    //qDebug() << "cutAfter: result: " << result << endl;
    return result;
}

QString HtmlParse::cutAfter(QString html, QString findIt, int num)
{
    QString result="empty"; int k=-1; int j;

    for(int i=0; i<num && k!=-1; i++){
        k = html.indexOf(findIt,k+1);
    }

    //k = html.indexOf("</",k);
    //k = findEnd(html,k+1,html.size(),1);


    if(k==-1) return result;
    else
    {
        //k += findIt.size();
        j = findEnd(html,k,html.size(),1);
    }

    if(j!=-1)result = html.mid(k,j);

    //qDebug() << "cutAfter: result: " << result << endl;
    return result;
}

QString HtmlParse::cutAfter(QString html, QString findIt, int num, int levelUp)
{
    QString result="empty"; int k=-1; int j;

    for(int i=0; i<num; i++){
        k = html.indexOf(findIt,k+1);
    }

    if(k==-1) return result;
    else
    {
        //k += findIt.size();
        j = findEnd(html,k,html.size(),levelUp);
    }

    if(j!=-1) result = html.mid(k,j-k);

    //qDebug() << "cutAfter: result: " << result << endl;
    return result;
}

QString HtmlParse::cutAfterWith(QString html, QString findIt, int num, int levelUp)
{
    QString result="empty"; int k=-1; int j;

    for(int i=0; i<num; i++){
        k = html.indexOf(findIt,k+1);
    }

    if(k==-1) return result;
    else
    {
        //k += findIt.size();
        j = findEnd2(html,k,html.size(),levelUp);
    }

    if(j!=-1) result = html.mid(k,j-k);

    //qDebug() << "cutAfter: result: " << result << endl;
    return result;
}

QString HtmlParse::cutUrlSection(QString html, int num)
{
    int a = 0;
    for(int i=0; i<num; i++)
    {
        a = html.indexOf("/",a)+1;
    }
    int b = html.indexOf("/",a);
    return html.mid(a,b-a);
}

QString HtmlParse::findText(QString str, QString xstr)
{
    //qDebug() << "findField: input: " << str << endl;
    QString result="empty";

    int a = str.indexOf("<"+xstr);
    int b = str.indexOf("</" + xstr + ">",a);
    a = str.indexOf(">",a)+1;
    if(a<b) result = str.mid(a,b-a);

    //qDebug() << "findField: result: " << result << endl;
    return result;
}

QString HtmlParse::findText(QString str, QString xstr, int num)
{
    //qDebug() << "findField: input: " << str << endl;
    QString result="empty"; int a=0;

    for(int i=0; i<num; i++)
    {
        a = str.indexOf("<"+xstr,a)+1;
    }

    int b = str.indexOf("</" + xstr + ">",a);
    a = str.indexOf(">",a)+1;
    if(a<b) result = str.mid(a,b-a);

    //qDebug() << "findField: result: " << result << endl;
    return result;
}

QString HtmlParse::findText(QString str, QString xstr, QString className)
{
    QString result="empty", fstr = "<"+xstr+" class="+'"'+className+'"';

    int a = str.indexOf(fstr);
    int b = str.indexOf("</" + xstr + ">",a);
    a = str.indexOf(">",a)+1;
    if(a<b) result = str.mid(a,b-a);

    return result;
}

QString HtmlParse::findText(QString str, QString xstr, QString className, int num)
{
    QString result="empty", fstr = "<"+xstr+" class="+'"'+className+'"';
    int a=0;

    for(int i=0; i<num; i++)
    {
        a = str.indexOf(fstr,a)+1;
    }

    int b = str.indexOf("</" + xstr + ">",a);
    a = str.indexOf(">",a)+1;
    if(a<b) result = str.mid(a,b-a);

    return result;
}

QString HtmlParse::findField(QString str, QString xstr)
{
    QString result="empty";

    int i = str.indexOf(xstr+"=") + xstr.size()+1;

    int a = str.indexOf('"',i)+1;
    int b = str.indexOf('"',a);

    result = str.mid(a,b-a);

    //qDebug() << "findField: result: " << result << endl;
    return result;
}

QString HtmlParse::findField(QString str, QString xstr, int num)
{
    QString result="empty"; int i=0;

    for(int j=0; j<num; j++){
        i = str.indexOf(xstr+"=",i) + xstr.size()+1;
    }

    int a = str.indexOf('"',i)+1;
    int b = str.indexOf('"',a);

    result = str.mid(a,b-a);

    //qDebug() << "findField: result: " << result << endl;
    return result;
}

QString HtmlParse::findImage(QString html)
{
    QString result = "empty";

    int i = html.indexOf("src=");
    if(i==-1) return result;

    int a = html.indexOf('"',i);
    if(a==-1) return result;
    int b = html.indexOf('"',a+1);
    if(b==-1) return result;

    return html.mid(a+1,b-a-1);
}

QString HtmlParse::findImage(QString html, int num)
{
    QString result = "empty"; int i=-1;

    for(int j=0; j<num; j++){
        i = html.indexOf("src=",i+1);
        if(i==-1) return result;
    }

    int a = html.indexOf('"',i);
    if(a==-1) return result;
    int b = html.indexOf('"',a+1);
    if(b==-1) return result;

    return html.mid(a+1,b-a-1);
}

QString HtmlParse::findAdress(QString html)
{
    QString result = "empty";

    int i = html.indexOf("href=");
    if(i==-1) return result;

    int a = html.indexOf('"',i);
    if(a==-1) return result;
    int b = html.indexOf('"',a+1);
    if(b==-1) return result;

    return html.mid(a+1,b-a-1);
}

QString HtmlParse::findAdress(QString html, int num)
{
    QString result = "empty"; int i=-1;

    for(int j=0; j<num; j++){
        i = html.indexOf("href=",i+1);
        if(i==-1) return result;
    }

    int a = html.indexOf('"',i);
    if(a==-1) return result;
    int b = html.indexOf('"',a+1);
    if(b==-1) return result;

    return html.mid(a+1,b-a-1);
}

QString HtmlParse::cutAfterAndFindText(QString html, QString findIt, QString xstr)
{
    return findText(cutAfter(html,findIt),xstr);
}

long int HtmlParse::findEnd(QString html, int sp, int fp, int j)
{
    bool res = (j==0) ? (true) : (false),corr = (j<1) ? (true) : (false); int i=-1;
    QString str = html.mid(sp,fp-sp-1);
    while(true)
    {
        i = str.indexOf("<",i+1);
        if(i!=-1)
        {
            if(str.at(i+1)=="/")
            {
                j--;
                if(j==0)
                    if(res) return i+sp;
                    else res = true;
            }
            else if(!(str.at(i+1)=="i" && str.at(i+2)=="m" && str.at(i+3)=="g"))
            {
                j++;
            }
        }
        else break;
    }
    qDebug() << "findEnd: error" << endl;
    return -1;
}

long int HtmlParse::findEnd2(QString html, int sp, int fp, int j)
{
    bool corr = (j<1) ? (true) : (false); int i=-1;
    QString str = html.mid(sp,fp-sp-1);
    while(true)
    {
        i = str.indexOf("<",i+1);
        if(i!=-1)
        {
            if(str.at(i+1)=="/")
            {
                j--;
                if(j==0)
                    return i+sp;
            }
            else if(!(str.at(i+1)=="i" && str.at(i+2)=="m" && str.at(i+3)=="g"))
            {
                j++;
            }
        }
        else break;
    }
    qDebug() << "findEnd: error" << endl;
    return -1;
}
