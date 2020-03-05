
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
  acc[i].addEventListener("click", function(){
      
    /*
    var otherElements = document.getElementsByClassName("accordionTitleButton");
    var j;
    for (j = 0; j < otherElements.length; j++)
    {
        var otherPanel = otherElements[j].nextElementSibling;
        if (otherPanel.style.maxHeight)
        {
            otherPanel.style.maxHeight = null;
        }
    }
     */
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
            titleTextContent.style.textAlign = "left";
                
            panelContent.style.flexDirection  = "row-reverse";
        }
        else
        {
            titleContent.style.flexDirection  = "row";
            
            var titleTextContent = titleContent.querySelector(".articleTitleContent");
            titleTextContent.style.marginRight = "0";
            titleTextContent.style.marginLeft = "auto";
            titleTextContent.style.textAlign = "right";
            
            panelContent.style.flexDirection  = "row";
        }
        
    }
    
}


hideAllArticles();
displayVisibleArticleListCorrectly(".articleElement");




