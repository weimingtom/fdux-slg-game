from django.db import models

class Versions(models.Model):
    versions = models.IntegerField()
    createTime = models.DateTimeField()
    size = models.IntegerField()
    content = models.CharField(max_length=100)
    objectName = models.CharField(max_length=100)

class DownloadLog(models.Model):
    GUID = models.CharField(max_length=200)
    date = models.DateField()

class Quota(models.Model):
    date = models.DateField()
    quota = models.IntegerField()

class QuotaConfig(models.Model):
    maxQuota = models.IntegerField()

# Create your models here.
