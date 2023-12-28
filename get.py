from bs4 import BeautifulSoup as Soup
import requests
import shutil
import sys
import os

_DEBUG = False

def get_problem(contest_id, letter):
    url = f"https://codeforces.com/problemset/problem/{contest_id}/{letter}"
    content = Soup(requests.get(url).content, 'lxml')
    inp, out, _dir = *content.find_all("pre"), f"./Codeforces/{contest_id}/{letter}"

    try: os.makedirs(f"./Codeforces/{contest_id}/{letter}/")
    except: pass
    
    with open(f"{_dir}/input.txt", 'w') as f: f.write(inp.get_text(separator="\n").strip('\n'))
    with open(f"{_dir}/output.txt", 'w') as f: f.write(out.get_text(separator="\n").strip('\n'))
    shutil.copyfile("template.cpp", f"{_dir}/{contest_id}{letter}.cpp")

    print(f"Wrote to {_dir}/")

def main():
    if len(sys.argv) != 3:
        print('Usage: python get.py <contest_id> <letter>')
    else:
        contest_id, letter = sys.argv[1:]
        get_problem(contest_id, letter)

if __name__ == "__main__":
    if not _DEBUG: main()
    else: get_problem(4, "A")

