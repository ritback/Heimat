<%EnableSessionState=False
host = Request.ServerVariables("HTTP_HOST")

if host = "henriaribertdesjardins.com" or host = "www.henriaribertdesjardins.com" then response.redirect("https://www.henriaribertdesjardins.com/")

else
response.redirect("https://www.henriaribertdesjardins.com/error.html")
end if
%>