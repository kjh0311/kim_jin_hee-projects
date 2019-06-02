import re
import os
def mkdir_if_not_exist(folder_name):
    if not os.path.isdir(folder_name):
        os.mkdir(folder_name)


def file_to_list(filename):
    file_candidate = open(filename, "r")
    list_candidate = []

    for line in file_candidate:
        line = line.rstrip()
        list_candidate.append(line)

    file_candidate.close()

    return list_candidate


def count_coexists(list_articles, word1, word2):
    count = 0

    dir_name = word1+"-"+word2
    mkdir_if_not_exist(dir_name)
    os.chdir(dir_name)

    # 한 기사안에 동시에 들어가는 것을 확인
    regex = "(" + word1 + ".*" + word2 + ")|(" + word2 + ".*" + word1 + ")"
    for article in list_articles:
        if bool(re.search(regex, article)) == True :
            count = count + 1

            if count > 0:
                continue
            
            # 두 단어가 한 기사에 동시에 들어간다면, 그 기사를 파일로 내보냄
            list_one_article = article.split("\t")
            file_name = list_one_article[0] + " " + list_one_article[2] +".html"
            regex_for_file = "[(\\)(/)(\")(\?)(\|)(<)(>)(\*)(\:)]"
            file_name = re.sub(regex_for_file, ' ', file_name)
            file = open(file_name, "w")
            file.write(list_one_article[3])
            file.close()
            

    os.chdir("..")
    return count



folder_name = "소셜네트워크서비스"
edge_list_folder_name = "edge list"
range_name1 = "20-"
range_name2 = "15-20"
range_name3 = "10-15"
range_name4 = "5-10"
range_name5 = "0-5"





def make_all_directories_if_not_exists():
    mkdir_if_not_exist(folder_name)
    os.chdir(folder_name)
    mkdir_if_not_exist(edge_list_folder_name)
    #mkdir_if_not_exist(range_name1)
    #mkdir_if_not_exist(range_name2)
    #mkdir_if_not_exist(range_name3)
    #mkdir_if_not_exist(range_name4)
    #mkdir_if_not_exist(range_name5)
    os.chdir("..")



# 코드는 여기서부터 실행됩니다.


list_tweet = file_to_list("Data_OnlySocialNetworkService2012_2016.txt")

make_all_directories_if_not_exists()
os.chdir(folder_name)
list_candidate = file_to_list("candidate.txt")

out_file1 = open("./" + edge_list_folder_name + "/" + range_name1 + ".csv", "w")
out_file2 = open("./" + edge_list_folder_name + "/" + range_name2 + ".csv", "w")
out_file3 = open("./" + edge_list_folder_name + "/" + range_name3 + ".csv", "w")
out_file4 = open("./" + edge_list_folder_name + "/" + range_name4 + ".csv", "w")
out_file5 = open("./" + edge_list_folder_name + "/" + range_name5 + ".csv", "w")
#out_file_0_50 = open("./" + edge_list_folder_name + "/" + range_name5 + ".csv", "w")

#print(list_tweet)

# 여기서 리스트를 만듬
for word1 in list_candidate:
    for word2 in list_candidate:
        if word1==word2 \
           or word1=="기자" or word2=="기자"\
           or word1=="이" or word2=="이"\
           or word1=="대" or word2=="대"\
           or word1=="전" or word2=="전"\
           :
            continue
        else:
            count = count_coexists(list_tweet, word1, word2)
            line = word1 + "," + word2 + "," + str(count) + "\n"

            #out_file.write(line)

            if count > 20:
                out_file1.write(line)
            elif count > 15:
                out_file2.write(line)
            elif count > 10:
                out_file3.write(line)
            elif count > 5:
                out_file4.write(line)
            else:
                out_file5.write(line)

os.chdir("..")
out_file1.close()
out_file2.close()
out_file3.close()
out_file4.close()
out_file5.close()


# 파일 쓰기 하면 끝