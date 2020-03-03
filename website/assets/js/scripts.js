
/* Set the width of the sidebar to 250px and the left margin of the page content to 250px */
function openNav() {
  document.getElementById("sidebarNav").style.width = "250px";
  //document.getElementById("content").style.marginLeft = "250px";
}

/* Set the width of the sidebar to 0 and the left margin of the page content to 0 */
function closeNav() {
  document.getElementById("sidebarNav").style.width = "0";
  //document.getElementById("content").style.marginLeft = "0";
}




var acc = document.getElementsByClassName("accordionTitleButton");
var i;

for (i = 0; i < acc.length; i++) {
  acc[i].addEventListener("click", function() {
    this.classList.toggle("activeAccordionButton");
    var panel = this.nextElementSibling;
    if (panel.style.maxHeight) {
      panel.style.maxHeight = null;
    } else {
      panel.style.maxHeight = panel.scrollHeight + "px";
    } 
  });
}



function hideAllArticles()
{
	var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;
    // hide all articles
    for (var i = 0; i < articleElementsNbr; i++)
    {
        allArticleElements[i].style.display = "none";
    }
}

function displayAllArticles()
{
	var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;
    // hide all articles
    for (var i = 0; i < articleElementsNbr; i++)
    {
        allArticleElements[i].style.display = "block";
    }
}


function displayVisibleArticleListCorrectly(tag)
{
    hideAllArticles();
    
    // place correctly
    var visibleArticleElements = document.querySelectorAll(tag);
    var visibleArticleElementsNbr = visibleArticleElements.length;
    
	for (var i = 0; i < visibleArticleElementsNbr; i++)
	{
        visibleArticleElements[i].style.display = "block";
        
        var titleContent = visibleArticleElements[i].querySelector(".accordionTitleButton");
        var panelContent = visibleArticleElements[i].querySelector(".panelContent");
        if (i%2==1)
        {
            titleContent.style.flexDirection  = "row-reverse";
            
            var titleTextContent = titleContent.querySelector(".articleTitleContent");
            titleTextContent.style.marginRight = "auto";
            titleTextContent.style.marginLeft = "0";
                
            panelContent.style.flexDirection  = "row-reverse";
        }
        else
        {
            titleContent.style.flexDirection  = "row";
            
            var titleTextContent = titleContent.querySelector(".articleTitleContent");
            titleTextContent.style.marginRight = "0";
            titleTextContent.style.marginLeft = "auto";
            
            panelContent.style.flexDirection  = "row";
        }
        
    }
    
}


hideAllArticles();
displayVisibleArticleListCorrectly(".articleElement");




/*
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


*/





