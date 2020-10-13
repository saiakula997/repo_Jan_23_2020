import os
import argparse
class VigenereCipher(object):
    def __init__(self,key):
        print('Vigenere Cipher Encription')
        self.key=key
    
    def encode(self, text):    
        key=self.key
        ans=''
        for I,i in enumerate(text):
            if(ord('!')<=ord(i)<=ord('~')):
                I=I%len(key)
                if( ord(i)+ord(key[I])-ord('!') > ord('~') ):
                    ans+=(chr(ord('!')+(ord(i)+ord(key[I])-ord('!'))%ord('~')-1))
                else:
                    ans+=(chr(ord(i)+ord(key[I])-ord('!')))
            else:
                ans+=i
        return ans
    
    def decode(self, text):     
        key=self.key
        ans=''
        for I,i in enumerate(text):
            if(ord('!')<=ord(i)<=ord('~')):
                I=I%len(key)
                if( (ord('!')+ord(i)-ord(key[I])) < ord('!')):
                    ans+=(chr( ord('~')+(ord(i)-ord(key[I]))+1))
                else:
                    ans+=(chr( ord('!')+ord(i)-ord(key[I])))
            else:
                ans+=i
        return ans

def read_from_file(file_name):
    f=open(file_name,'r')
    data=f.read()
    f.close()
    return data

def write_to_file(file_name,data):
    f=open(file_name,'w')
    data=f.write(data)
    f.close()

def encode_from_file(file_name,obj):
    data=read_from_file(file_name)
    for _ in range(args.strength):
        data= obj.encode(data)
    write_to_file(file_name,data)
    print('encode file -> '+file_name)

def decode_from_file(file_name,obj):
    data=read_from_file(file_name)
    for _ in range(args.strength):
        data= obj.decode(data)
    write_to_file(file_name,data)    
    print('decode file -> '+file_name)

def encription_form_path(PATH,obj):
        try:
                for path in os.listdir(PATH):
                        encription_form_path(PATH+'/'+path,obj)
        except:
                if(args.encode):
                        encode_from_file(PATH,obj)
                elif(args.decode):   
                        decode_from_file(PATH,obj)
    
parser = argparse.ArgumentParser(description='Description of your program')
parser.add_argument('-i','--input_file', help='input file name', required=False)
parser.add_argument('-e','--encode', help='encode password', required=False)
parser.add_argument('-d','--decode', help='decode password', required=False)
parser.add_argument('-f','--folder',help='folder name',required=False)
parser.add_argument('-s','--strength', help='encription strength', type=int, default=1, required=False)
args =(parser.parse_args())

if(args.input_file):
    PATH=args.input_file
elif(args.folder):
    PATH=args.folder
else:
    exit('Need --input_file or --folder\nUse -h for help')

if(args.encode):
    pswd=args.encode
elif(args.decode):
    pswd=args.decode
else:
    exit('Need --encode or --decode\nUse -h for help')


obj=VigenereCipher(pswd)
encription_form_path(PATH,obj)

