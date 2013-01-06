'''
Created on 2013-1-6

@author: qi.dong
'''
import os
import sys

if __name__ == '__main__':
    ResourceName = raw_input('Resource Name :')
    size = raw_input('Size:')
    size =str(size)
    mode = raw_input('Mode:')
    file = open('%s.txt'%ResourceName, 'wb')
    file.write("    <Resource type=\"ResourceImageSet\" name=\"%s\">\n"%ResourceName)
    ExportList=[]
    fileList = os.listdir(".")
    for line in fileList:
        if line.split('.')[1]=="png" :
            ExportList.append(line)

    for efile in ExportList:
        filePrevName=efile.split('.')[0]
        if mode=='1':
            file.write(
"""
        <Group name="%s" texture="%s.png" size="45 45">
            <Index name="disabled">
                <Frame point="0 0"/>
            </Index>
            <Index name="normal">
                <Frame point="45 0"/>
            </Index>
            <Index name="highlighted">
                <Frame point="90 0"/>
            </Index>
            <Index name="pushed">
                <Frame point="135 0"/>
            </Index>
        </Group>\n
"""%(filePrevName,filePrevName))
        else:
            file.write(
"""
        <Group name="%s" texture="%s.png" size="%s %s">
            <Index name="normal">
                <Frame point="0 0"/>
            </Index>
        </Group>\n
"""%(filePrevName,filePrevName,size,size))
        
    file.write("    </Resource>")
    file.close()