# -*- coding: cp936 -*-
import xlrd
import sys

from xml.etree.ElementTree import ElementTree
from xml.etree.ElementTree import Element
from xml.etree.ElementTree import SubElement
from xml.etree.ElementTree import dump
from xml.etree.ElementTree import Comment
from xml.etree.ElementTree import tostring

me, args = sys.argv[0], sys.argv[1:]

def PweaponData(table,xmlTree,stringTree):
    root = Element("PweaponData")
    stringTreeRoot = Element("PweaponData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        if table.cell(i,13).value=="" :
            return

        print "PWwaponData:"+table.cell(i,13).value
        name = table.cell(i,13).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,14).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,15).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,16).value)})
        SubElement(item,  'Mesh', {'type' : "String",'value':str(table.cell(i,17).value)})
        SubElement(item,  'Mat', {'type' : "String",'value':str(table.cell(i,18).value)})
        SubElement(item,  'PU', {'type' : "String",'value':str(table.cell(i,19).value)})
        SubElement(item,  'PUVector', {'type' : "String",'value':str(table.cell(i,20).value)})
        SubElement(item,  'AniGroup', {'type' : "String",'value':str(table.cell(i,21).value)})
        SubElement(item,  'Icon', {'type' : "String",'value':str(table.cell(i,22).value)})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,23).value})

def SweaponData(table,xmlTree,stringTree):
    root = Element("SweaponData")
    stringTreeRoot = Element("SweaponData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        print "SWwaponData:"+table.cell(i,15).value
        name = table.cell(i,15).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,16).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,17).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,18).value)})
        SubElement(item,  'Mesh', {'type' : "String",'value':str(table.cell(i,19).value)})
        SubElement(item,  'Mat', {'type' : "String",'value':str(table.cell(i,20).value)})
        SubElement(item,  'PU', {'type' : "String",'value':str(table.cell(i,21).value)})
        SubElement(item,  'PUVector', {'type' : "String",'value':str(table.cell(i,22).value)})
        SubElement(item,  'AniGroup', {'type' : "String",'value':str(table.cell(i,23).value)})
        SubElement(item,  'Icon', {'type' : "String",'value':str(table.cell(i,24).value)})
        SubElement(item,  'MaxRange', {'type' : "Int",'value':str(int(table.cell(i,13).value))})
        SubElement(item,  'MinRange', {'type' : "Int",'value':str(int(table.cell(i,14).value))})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,25).value})

def HorseData(table,xmlTree,stringTree):
    root = Element("HorseData")
    stringTreeRoot = Element("HorseData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        print "HorseData:"+table.cell(i,13).value
        name = table.cell(i,13).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,14).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,15).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,16).value)})
        SubElement(item,  'Mesh', {'type' : "String",'value':str(table.cell(i,17).value)})
        SubElement(item,  'Mat', {'type' : "String",'value':str(table.cell(i,18).value)})
        SubElement(item,  'Icon', {'type' : "String",'value':str(table.cell(i,19).value)})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,20).value})

def ShieldData(table,xmlTree,stringTree):
    root = Element("ShieldData")
    stringTreeRoot = Element("ShieldData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        print "ShieldData:"+table.cell(i,13).value
        name = table.cell(i,13).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,14).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,15).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,16).value)})
        SubElement(item,  'Mesh', {'type' : "String",'value':str(table.cell(i,17).value)})
        SubElement(item,  'Mat', {'type' : "String",'value':str(table.cell(i,18).value)})
        SubElement(item,  'PU', {'type' : "String",'value':str(table.cell(i,19).value)})
        SubElement(item,  'PUVector', {'type' : "String",'value':str(table.cell(i,20).value)})
        SubElement(item,  'Icon', {'type' : "String",'value':str(table.cell(i,21).value)})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,22).value})

def ArmorData(table,xmlTree,stringTree):
    root = Element("ArmorData")
    stringTreeRoot = Element("ArmorData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        print "ArmorData:"+table.cell(i,13).value
        name = table.cell(i,13).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,14).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,15).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,16).value)})
        SubElement(item,  'Icon', {'type' : "String",'value':str(table.cell(i,17).value)})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,18).value})

def SoilderData(table,xmlTree,stringTree):
    root = Element("SoilderData")
    stringTreeRoot = Element("SoilderData")
    xmlTree.append(root)
    stringTree.append(stringTreeRoot)
    nrows = table.nrows
    for i in range(3,nrows):
        print "SoilderData:"+table.cell(i,13).value
        name = table.cell(i,13).value
        item = Element(name)
        stringItem = Element(name)
        root.append(item)
        stringTreeRoot.append(stringItem)

        SubElement(item,  'Type', {'type' : "Int",'value':str(int(table.cell(i,14).value))})
        SubElement(item,  'Value', {'type' : "Int",'value':str(int(table.cell(i,15).value))})
        SubElement(item,  'Script', {'type' : "String",'value':str(table.cell(i,16).value)})
        SubElement(item,  'Randomness', {'type' : "Int",'value':str(int(table.cell(i,12).value*100))})

        attr=Element('AttrModifer')
        item.append(attr)
        SubElement(attr,  'Type', {'type' : "Int",'value':'0'})
        SubElement(attr,  'Attack', {'type' : "Float",'value':str(table.cell(i,2).value)})
        SubElement(attr,  'RangedAttack', {'type' : "Float",'value':str(table.cell(i,3).value)})
        SubElement(attr,  'Defence', {'type' : "Float",'value':str(table.cell(i,4).value)})
        SubElement(attr,  'Formation', {'type' : "Float",'value':str(table.cell(i,5).value)})
        SubElement(attr,  'Initiative', {'type' : "Float",'value':str(table.cell(i,6).value)})
        SubElement(attr,  'ActionPoint', {'type' : "Float",'value':str(table.cell(i,7).value)})
        SubElement(attr,  'Detection', {'type' : "Float",'value':str(table.cell(i,8).value)})
        SubElement(attr,  'Covert', {'type' : "Float",'value':str(table.cell(i,9).value)})
        SubElement(attr,  'Toughness', {'type' : "Float",'value':str(table.cell(i,10).value)})
        SubElement(attr,  'Conter', {'type' : "Float",'value':str(table.cell(i,11).value)})

        SubElement(stringItem,  'Name', {'type' : "String",'value':table.cell(i,0).value})
        #SubElement(stringItem,  'Describe', {'type' : "String",'value':table.cell(i,18).value})


def indent(elem, level=0):
    i = "\n" + level*"\t"
    if len(elem):
        if not elem.text or not elem.text.strip():
            elem.text = i + "\t"
        for e in elem:
            indent(e, level+1)
            if not e.tail or not e.tail.strip():
                e.tail = i + "\t"
        if not e.tail or not e.tail.strip():
            e.tail = i
    else:
        if level and (not elem.tail or not elem.tail.strip()):
            elem.tail = i

for arg in args:
    print >>sys.stderr, 'extracting data from', arg
    book = xlrd.open_workbook(arg)

    xmlTree = ElementTree()
    stringTree = ElementTree()

    xmlTreeRoot = Element('StaticData')
    xmlTree._setroot(xmlTreeRoot)

    stringTreeRoot = Element('StaticData')
    stringTree._setroot(stringTreeRoot)  

    SoilderData(book.sheets()[6],xmlTreeRoot,stringTreeRoot)
    PweaponData(book.sheets()[1],xmlTreeRoot,stringTreeRoot)
    SweaponData(book.sheets()[2],xmlTreeRoot,stringTreeRoot)
    HorseData(book.sheets()[3],xmlTreeRoot,stringTreeRoot)
    ShieldData(book.sheets()[4],xmlTreeRoot,stringTreeRoot)
    ArmorData(book.sheets()[5],xmlTreeRoot,stringTreeRoot)

    indent(xmlTreeRoot)
    indent(stringTreeRoot)
    xmlTree.write('data.xml')
    stringTree.write('string.xml',"utf-8")

    print "Over"
        
