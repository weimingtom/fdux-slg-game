from django.http import HttpResponse
from fduxupdate.versions.models import *
import datetime

def getVersions(request):
    if 'Versions' in request.GET:
        VerSet = Versions.objects.filter(versions__gt=int(request.GET['Versions'])).order_by("versions")
        if len(VerSet) == 0:
            message = "0"
        else:
            ver=VerSet[0]
            message = '%u|%s|%u|%s' % (ver.versions,ver.createTime,ver.size,ver.content)
    else:
        message = '0'
    return HttpResponse(message)

def download(request):
    if 'Versions' in request.GET and 'GUID' in request.GET:
        VerSet = Versions.objects.filter(versions=int(request.GET['Versions']))
        if len(VerSet) == 0:
            message = "0"
        else:
            max=QuotaConfig.objects.all()[0]
            QuotaSet=Quota.objects.filter(date__gte=datetime.date.today())
            if len(QuotaSet)==0:
                quota=Quota(date=datetime.date.today(),quota=VerSet[0].size)
                quota.save()
                
                log=DownloadLog(GUID=request.GET['GUID'],date=datetime.date.today())
                log.save()
            else:
                if QuotaSet[0].quota+VerSet[0].size<max.maxQuota:
                    DownloadLogSet=DownloadLog.objects.filter(GUID=request.GET['GUID'])
                    
                    if len(DownloadLogSet)<=10:
                        QuotaSet[0].quota=QuotaSet[0].quota+VerSet[0].size
                        QuotaSet[0].save()
                        
                        log=DownloadLog(GUID=request.GET['GUID'],date=datetime.date.today())
                        log.save()
                        
                        message = VerSet[0].objectName
                    else:
                        message ='0'
                else:
                    message = '0'
    else:
        message = '0'
    return HttpResponse(message)
    
        