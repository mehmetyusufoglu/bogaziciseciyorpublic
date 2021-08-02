import ssl, smtplib
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart

import csv

# Code inspired from here:
# https://realpython.com/python-send-email/



class EmailSender:

    initialized = False

    _from = "noreply@bogaziciseciyor.org"
    _reply_to = "Do not reply to this email.<noreply@bogaziciseciyor.org>"

    def __init__(self, host, port, username, password):
        try:
            self.context = ssl.create_default_context()

            self.server = smtplib.SMTP(smtp_server, port)
            self.server.ehlo()
            self.server.starttls(context=self.context)
            self.server.ehlo()
            self.server.login(sender_email, password)
            self.initialized = True
        except Exception as e:
            print(e.with_traceback())

    def send_accept_mail(self, to, code):
        if self.initialized:
            msg = MIMEMultipart("alternative")
            msg["Subject"] = "Seçime katılım için kodunuz"
            msg["From"] = self._from
            msg["Reply-To"] = self._reply_to
            msg["To"] = to

            with open("template/textTemplate.txt", "r") as f:
                textPlain = f.read().replace(r"{{code}}", code)
            
            with open("template/htmlTemplate.html", "r") as f:
                textHtml = f.read().replace(r"{{code}}", code)
            
            part1 = MIMEText(textPlain, "plain")
            part2 = MIMEText(textHtml, "html")

            msg.attach(part1)
            msg.attach(part2)

            self.server.sendmail("noreply@karacasoft.com", to, msg.as_string())
    
    def send_reject_mail(self, to, reason):
        if self.initialized:
            msg = MIMEMultipart("alternative")
            msg["Subject"] = "Seçime katılımız reddedildi"
            msg["From"] = self._from
            msg["Reply-To"] = self._reply_to
            msg["To"] = to

            with open("template/reject/textTemplate.txt", "r") as f:
                textPlain = f.read().replace(r"{{reason}}", reason)
            
            with open("template/reject/htmlTemplate.html", "r") as f:
                textHtml = f.read().replace(r"{{reason}}", reason)
            
            part1 = MIMEText(textPlain, "plain")
            part2 = MIMEText(textHtml, "html")

            msg.attach(part1)
            msg.attach(part2)

            self.server.sendmail("noreply@karacasoft.com", to, msg.as_string())


emailSender = EmailSender(smtp_server, port, sender_email, password)

with open("TestHashes2.csv", "r") as testhashfile:
    csvfile = csv.reader(testhashfile, delimiter=",", quotechar='"')

    next(csvfile)
    for row in csvfile:
        print(row)
        emailSender.send_accept_mail(row[0], row[1])
