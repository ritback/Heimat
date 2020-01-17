
// Random color for the head title
(function(){
	var randomColor = Math.floor(Math.random()*15461355).toString(16);
	var head_title = document.querySelector(".head_title");
	head_title.style.color = "#" + randomColor; 
}) ();

// Random color for the article titles
(function()
{
	var randomColor = Math.floor(Math.random()*11119017).toString(16);
	var allContentArticle = document.querySelectorAll(".content_article h3");
	var articleNbr = allContentArticle.length;
	for (var i = 0; i < articleNbr; i++)
	{
       allContentArticle[i].style.color = "#" + randomColor;
    }
}) ();

// Height for the element of the menu
function navElementsResize()
{
	//var navMenu = document.querySelector(".nav_menu");
	//var navMenuHeight = getComputedStyle(navMenu).width;
	
	var allNavElements = document.querySelectorAll(".nav_elements");
	var navElementsNbr = allNavElements.length;
	for (var i = 0; i < navElementsNbr; i++)
	{
       allNavElements[i].style.height = 100/navElementsNbr + "%";
    }
}

navElementsResize();
window.addEventListener("resize", navElementsResize, false);

// height for video
function videosResize()
{
	var allVideo = document.querySelectorAll(".content_article_vid");
	var videoNbr = allVideo.length;
	for (var i = 0; i < videoNbr; i++)
	{
		var vidHeight = allVideo[i].offsetWidth * 9 / 16;
		allVideo[i].style.height = vidHeight + "px";
    }
}
videosResize();

window.addEventListener("resize", videosResize, false);


// height for pdf
function pdfResize()
{
	var allPDF = document.querySelectorAll(".content_article_pdf");
	var pdfNbr = allPDF.length;
	for (var i = 0; i < pdfNbr; i++)
	{
		var pdfHeight = allPDF[i].offsetWidth * 42 / 27;
		allPDF[i].style.height = pdfHeight + "px";
		allPDF[i].contentDocument.location.reload();
    }
}
pdfResize();

window.addEventListener("resize", pdfResize, false);








