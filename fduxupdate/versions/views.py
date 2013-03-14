from django.http import HttpResponse
from fduxupdate.versions.models import Versions

def getVersions(request):
    if 'Versions' in request.GET:
        VerSet = Versions.objects.filter(versions__gt=int(request.GET['Versions'])).order_by("versions")
        if len(VerSet) == 0:
            message = "0"
        else:
            ver=VerSet[0]
            message = '%u|%s|%u|%s|%s' % (ver.versions,ver.createTime,ver.size,ver.content,ver.objectName)
    else:
        message = '0'
    return HttpResponse(message)

def download(request):
   # if 'object' in request.GET:
    
        