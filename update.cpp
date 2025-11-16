#include <iostream>
#include <string>
#include <fstream>
#include <windows.h>
using namespace std;

string get_character() {
    string file_path;
    int chac_num, flag=0;
    cout << "Choose a character: 1.烬行 2.铃弗瑞迪尔 3.斯沃德麦伦 4.谶 5.度漪 6.塔拉撒里昂 7.赛博恩 8.无可奉告哥 9.服务型机器人" << endl;
    while (flag == 0)
    {    
        cout << "Enter the number: ";
        cin >> chac_num;
        switch(chac_num) {
            case 1:
                file_path = "JinXing";
                flag = 1;
                break;
            case 2:
                file_path = "LingLan";
                flag = 1;
                break;
            case 3:
                file_path = "SwordMelon";
                flag = 1;
                break;
            case 4:
                file_path = "Chen";
                flag = 1;
                break;
            case 5:
                file_path = "DoYi";
                flag = 1;
                break;
            case 6:
                file_path = "TaTa";
                flag = 1;
                break;
            case 7:
                file_path = "Cyborn";
                flag = 1;
                break;
            case 8:
                file_path = "Unknown1";
                flag = 1;
                break;
            case 9:
                file_path = "Unknown2";
                flag = 1;
                break;
            case 0:
                return 0;
            default:
                cout << "invalid input." << endl;
                break;
        }
    }

    return file_path;
}

struct UpdateContent
{
    string date;
    string media_path;
    string content;
    string venue;
    string source;
    string source_link;
    string title;
};

UpdateContent get_text_content(){
    UpdateContent new_content;
    string img_name;
    cout << "Enter date(yyyy.mm.dd): "; cin >> new_content.date;
    cout << "Enter venue: "; cin >> new_content.venue;
    cout << "Enter image file name: "; cin >> img_name;
    new_content.media_path = "../images/img/" + img_name;
    cout << "Enter content: "; cin >> new_content.content;
    return new_content;
}

int conformation() {
    int choice = 100;
    int flag = 0;
    while (flag == 0) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {  // not an integer
            cin.clear();   // clear error flags
            cin.ignore(1000, '\n'); // discard invalid input
            cout << "Invalid input, please enter 0 or 1." << endl;
            continue;
        }

        if (choice == 0 || choice == 1) {
            cout << choice << endl;
            flag = 1;
        } else {
            cout << "Invalid input," << endl;
        }
    }
    return choice;
}


int update_text_file(string file_path, UpdateContent new_content) {
    string full_content;
    ofstream outfile;
    full_content =
        "<tbody>\n"
        "    <tr>\n"
        "        <td>" + new_content.date + "<br>" + new_content.venue + "</td>\n"
        "        <td style='text-align:center; vertical-align:middle;'>\n"
        "            <img src='" + new_content.media_path + "' "
        "style='max-width:100%; max-height:100%; display:block; margin:auto;'>\n"
        "        </td>\n"
        "        <td class='sticky-cell'>" + new_content.content + "<span class='bottom-right'> </span></td>\n"
        "    </tr>\n"
        "</tbody>";
    
        cout << "Confirm update? 1.Yes 0.No" << endl;
    if (conformation() == 1) {
        outfile.open(file_path, ios::app);
        if (!outfile) {
            cerr << "Error: Could not open file for appending!" << endl;
            return 1;
        }
        outfile << full_content;

        outfile.close();
        cout << "Done update" << endl;
    }
    
}

string get_colour(string character) {
    string  colour;

    if (character == "JinXing") colour = "#bbbef2";
    else if (character == "LingLan") colour = "#ADF0DB";
    else if (character == "SwordMelon") colour = "#ecb898";
    else if (character == "Chen") colour = "#f0c4d5";
    else if (character == "DoYi") colour = "#fbe6a2";
    else if (character == "TaTa") colour = "#a8e1f0";
    else if (character == "Cyborn") colour = "#b3bfbf";
    else if (character == "Unknown1") colour = "#bce6ee";
    else if (character == "Unknown2") colour = "#bee5f0";

    return colour;
}

int text_update()
{
    string file_path;
    ofstream outfile;
    UpdateContent new_content;
    int flag;
    flag = 1;

    while (flag == 1)
    {
        file_path = "html/" + get_character() + ".html";
        cout << file_path << endl;

        new_content = get_text_content();
        cout << new_content.date << endl << new_content.venue << endl << new_content.media_path << endl << new_content.content << endl;

        update_text_file(file_path, new_content);

        cout << "Continue update for " << file_path << "?" << endl;
        flag = conformation();
    }
}

int update_type(){
    int flag, choice, type;
    flag = 1;

    cout << "Content type: 1.Opening video  2.Text  3.Video  4.News" << endl;
    while (flag == 1) {
        cout << "Enter the number: "; cin >> choice;
        switch (choice) {
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        case 3:
            return 3;
            break;
        case 4:
            return 4;
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid input. update type" << endl;
            break;
        }
    }
    
}

UpdateContent get_vid_content(){
    UpdateContent new_content;
    string vid_name;
    int num;

    cout << "Enter date(yyyy.mm.dd): "; cin >> new_content.date;
    cout << "Enter venue: "; cin >> new_content.venue;
    cout << "Enter video file name: "; cin >> vid_name;
    new_content.media_path = "../video/" + vid_name + ".mp4";
    cout << "Source: 1.微博 2.抖音  3.Bilibili 4.Other" << endl; 
    cout << "Enter number: "; cin >> num;
    switch (num) {
    case 1:
        new_content.source = "蒲熠星微博";
        break;
    case 2:
        new_content.source = "蒲熠星抖音";
        break;
    case 3:
        new_content.source = "蒲熠星B站";
        break;
    case 4:
        cin >> new_content.source;
        break;
    }
    cout << "Source link: "; cin >> new_content.source_link;
    cout << "Video Content: "; cin >> new_content.content;

    return new_content;
}

int update_op_file(string character, UpdateContent new_content) {
    string full_content;
    ofstream outfile;
    string file_path, colour;

    file_path = "html/" + character + "_op.html";
    colour = get_colour(character);

    full_content =
        "    <thead>\n"
        "        <tr style=\"background-color: " + colour + "\">\n"
        "            <th>" + new_content.date + "<br>" + new_content.venue + "</th>\n"
        "        </tr>\n"
        "    </thead>\n"
        "    <tbody>\n"
        "        <tr> <td>\n"
        "            <div class=\"op-vid-con\"> <video class=\"op-vid\" controls>\n"
        "                <source src='" + new_content.media_path + "' type='video/mp4'> Your browser does not support the video tag."
        "            </video> </div>\n"
        "            视频来源：<a href='" + new_content.source_link + "'>" + new_content.source + "</a>\n"
        "        </td> </tr>\n"
        "    </tbody>\n";

        cout << "Confirm update? 1.Yes 0.No" << endl;
    if (conformation() == 1) {
        outfile.open(file_path, ios::app);
        if (!outfile) {
            cerr << "Error: Could not open file for appending!" << endl;
            return 1;
        }
        outfile << full_content;

        outfile.close();
        cout << "Done update" << endl;
    }
    
}

int op_update() {
    string character;
    ofstream outfile;
    UpdateContent new_content;
    int flag;
    flag = 1;

    while (flag == 1)
    {
        character = get_character();
        cout << character << endl;

        new_content = get_vid_content();
        cout << new_content.date << endl << new_content.venue << endl << new_content.media_path << endl << new_content.source << new_content.source_link << endl;

        update_op_file(character, new_content);

        cout << "Continue update for " << character << " opening file?" << endl;
        flag = conformation();
    }
}

int update_vid_file(string character, UpdateContent new_content) {
    string full_content;
    ofstream outfile;
    string file_path;

    file_path = "html/" + character + "_vid.html";

full_content =
"    <tbody>\n"
"      <tr>\n"
"        <td style='text-align: center;'> <div class='op-vid-con'> <video class='op-vid' controls>\n"
"                <source src='" + new_content.media_path + "' type='video/mp4'> Your browser does not support the video tag.\n"
"            </video> </div>\n"
"            视频来源：<a href='" + new_content.source_link + "'>" + new_content.source + "</a>\n"
"        </td>\n"
"        <td class='sticky-cell'> <span class='date'>" + new_content.date + "</span><br>\n" 
+ new_content.content +
"        <span class='bottom-right'> </span></td>\n"
"      </tr>\n"
"    </tbody>";
    cout << "Confirm update? 1.Yes 0.No" << endl;
    if (conformation() == 1) {
        outfile.open(file_path, ios::app);
        if (!outfile) {
            cerr << "Error: Could not open file for appending!" << endl;
            return 1;
        }
        outfile << full_content;

        outfile.close();
        cout << "Done update" << endl;
    }
    
}

int vid_update() {
    string character;
    ofstream outfile;
    UpdateContent new_content;
    int flag;
    flag = 1;

    while (flag == 1)
    {
        character = get_character();
        cout << character << endl;

        new_content = get_vid_content();
        cout << new_content.date << endl << new_content.source << endl << new_content.source_link << endl << new_content.content;

        update_vid_file(character, new_content);

        cout << "Continue update for " << character << " video file?" << endl;
        flag = conformation();
    }

}

UpdateContent gets_news_content_img(){
    UpdateContent new_content;
    string img_name;
    int num;

    cout << "Enter date(yyyy.mm.dd): "; cin >> new_content.date;
    cout << "Enter news title: "; cin >> new_content.title;
    cout << "Enter image file name: "; cin >> img_name;
    new_content.media_path = "../images/news/" + img_name;
    cout << "Enter content: "; cin >> new_content.content;
    cout << "Source: 1.微博 2.抖音  3.Bilibili 4.Other" << endl; 
    cout << "Enter number: "; cin >> num;
    switch (num) {
    case 1:
        new_content.source = "蒲熠星微博";
        new_content.source_link = "https://m.weibo.cn/u/2882733894?luicode=10000011&lfid=1005055838726144&featurecode=n";
        break;
    case 2:
        new_content.source = "蒲熠星抖音";
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    case 3:
        new_content.source = "蒲熠星B站";
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    case 4:
        cout << "Enter source: "; cin >> new_content.source;
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    }
    return new_content;
}

UpdateContent gets_news_content_vid(){
    UpdateContent new_content;
    string vid_name;
    int num;

    cout << "Enter date(yyyy.mm.dd): "; cin >> new_content.date;
    cout << "Enter news title: "; cin >> new_content.title;
    cout << "Enter video file name: "; cin >> vid_name;
    new_content.media_path = "../video/news/" + vid_name + ".mp4";
    cout << "Enter content: "; cin >> new_content.content;
    cout << "Source: 1.微博 2.抖音  3.Bilibili 4.Other" << endl; 
    cout << "Enter number: "; cin >> num;
    switch (num) {
    case 1:
        new_content.source = "蒲熠星微博";
        new_content.source_link = "https://m.weibo.cn/u/2882733894?luicode=10000011&lfid=1005055838726144&featurecode=n";
        break;
    case 2:
        new_content.source = "蒲熠星抖音";
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    case 3:
        new_content.source = "蒲熠星B站";
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    case 4:
        cout << "Enter source: "; cin >> new_content.source;
        cout << "Source link: "; cin >> new_content.source_link;
        break;
    }
    return new_content;
}


int toClipboard(string s) {
    if (!OpenClipboard(nullptr)) return 0;
    if (!EmptyClipboard()) { CloseClipboard(); return 0; }

    // Convert UTF-8 -> UTF-16
    int wlen = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, nullptr, 0);
    if (wlen <= 0) { CloseClipboard(); return 0; }

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, wlen * sizeof(wchar_t));
    if (!hMem) { CloseClipboard(); return 0; }

    LPWSTR wbuf = static_cast<LPWSTR>(GlobalLock(hMem));
    if (!wbuf) { GlobalFree(hMem); CloseClipboard(); return 0; }

    MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, wbuf, wlen);
    GlobalUnlock(hMem);

    // Ownership of hMem transfers to the clipboard on success — do NOT free it.
    if (!SetClipboardData(CF_UNICODETEXT, hMem)) {
        GlobalFree(hMem); // only free on failure
        CloseClipboard();
        return 0;
    }

    CloseClipboard();
    return 1;}


int news_update_img() {
    UpdateContent new_content;
    int flag;
    string full_content;

    new_content = gets_news_content_img();
    full_content = 
"            <div class='col-md-4 news-item'>\n"
"            <h3>" + new_content.title +  "</h3>\n"
"            <span class='date'>" + new_content.date + "</span>\n"
"            <p>" + new_content.content + "</p>\n"
"            <div class='op-vid-con'> <img class='op-vid' src='" + new_content.media_path + "' > </div>\n"
"            <div class='news-comments'>\n"
"                <a href='javascript:void(0);' class='toggle-comments'>评论</a>\n"
"                <div class='collapse'>\n"
"                    <div class='card-body'>\n"
"                        <p style='display: flex; align-items: center; gap: 5px; margin: 0;'>\n"
"                            <strong>匿名用户:</strong>\n"
"                            <span>指路：</span> <a href='" + new_content.source_link + "'>" + new_content.source + "</a>\n"
"                        </p>\n                                      </div>\n                </div>\n            </div>\n        </div>\n";
    cout << "Full content: " << endl;cout << full_content << endl;
    cout << "Confirm update? 1.Yes 0.No" << endl;
    if (conformation() == 1) {
        toClipboard(full_content);
        cout << "Content copy to keyboard, please paste it at news.html" << endl;
    }
}

int news_update_vid() {
    UpdateContent new_content;
    int flag;
    string full_content;

    new_content = gets_news_content_vid();
    full_content = 
"            <div class='col-md-4 news-item'>\n"
"            <h3>" + new_content.title +  "</h3>\n"
"            <span class='date'>" + new_content.date + "</span>\n"
"            <p>" + new_content.content + "</p>\n"
"            <div class='op-vid-con'> <video class='op-vid' controls>\n"
"                <source src='" + new_content.media_path + "' type='video/mp4'> Your browser does not support the video tag.\n"
"            </video> </div>\n"
"            <div class='news-comments'>\n"
"                <a href='javascript:void(0);' class='toggle-comments'>评论</a>\n"
"                <div class='collapse'>\n"
"                    <div class='card-body'>\n"
"                        <p style='display: flex; align-items: center; gap: 5px; margin: 0;'>\n"
"                            <strong>匿名用户:</strong>\n"
"                            <span>指路：</span> <a href='" + new_content.source_link + "'>" + new_content.source + "</a>\n"
"                        </p>\n                                      </div>\n                </div>\n            </div>\n        </div>\n";
    cout << "Full content: " << endl;cout << full_content << endl;
    cout << "Confirm update? 1.Yes 0.No" << endl;
    if (conformation() == 1) {
        toClipboard(full_content);
        cout << "Content copy to keyboard, please paste it at news.html" << endl;
    }
}



int news_update() {
    int choice, flag;
    flag = 1;

    cout << "News update type: 1. Image news 2. Video news" << endl; cin >> choice;

    while (flag == 1) {
        switch (choice) {
        case 1:
            news_update_img();
            break;
        
        case 2:
            news_update_vid();
            break;
        
        default:
            break;
        }
        cout << "Continue news update? 1.Yes 0.No" << endl;
        flag = conformation();
    }
    
}

int main() {
    int flag;

    flag = 1;

    while (flag == 1) {
        switch (update_type()) {
            case 1:
                op_update();
                flag = 0;
                break;
            case 2:
                text_update();
                flag = 0;
                break;
            case 3: 
                vid_update();
                flag = 0;
                break;
            case 4:
                news_update();
                flag = 0;
                break;
            
            default:
                cout <<"Invalid input. main" << endl;
                break;
        }
        cout << "Continue update?" << endl;
        flag = conformation();
    }
    
}