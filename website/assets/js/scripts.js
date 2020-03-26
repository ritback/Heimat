
/* Set the width of the sidebar to 250px and the left margin of the page content to 250px */
function openNav() {
  document.getElementById("sidebarNav").style.width = "250px";
}

/* Set the width of the sidebar to 0 and the left margin of the page content to 0 */
function closeNav() {
  document.getElementById("sidebarNav").style.width = "0";
}


/* Set the width of the sidebar to 250px and the left margin of the page content to 250px */
function openAbout() {
  document.getElementById("aboutPanel").style.width = "100%";
}

/* Set the width of the sidebar to 0 and the left margin of the page content to 0 */
function closeAbout() {
  document.getElementById("aboutPanel").style.width = "0";
}


/******************************************************************************/

var acc = document.getElementsByClassName("accordionTitleButton");
var i, j;

for (i = 0; i < acc.length; i++) {
    acc[i].id = i;
    acc[i].addEventListener("click", function(){
      
      // close other panels
        var otherPanel;
      for(j = 0; j < acc.length; j++){
          // remove transition
          otherPanel = acc[j].nextElementSibling;
          otherPanel.classList.add("panelNoTransition");
          
          if (acc[j] != this){   
            if (otherPanel.style.maxHeight) {
                //close panel
                otherPanel.style.maxHeight = null;
                
            }
        }
      }
        
        
      
      // open / close the correct one.
      var panel = this.nextElementSibling;
      if (panel.style.maxHeight) {
          //close panel
          panel.style.maxHeight = null;
      }
      else {
          
            // place the panel on top;
          this.scrollIntoView({behavior: "instant", block: "start"});
      
          //window.location.hash = "#" + i;
          var headOffset = document.getElementById("head").getBoundingClientRect().bottom;
          window.scrollBy(0, -headOffset);
      
          
          // remove transition
          panel.classList.remove("panelNoTransition"); 
          panel.style.maxHeight = panel.scrollHeight + "px";
      }
      
      
        
      /*
      var headerBottom = document.getElementById("head").getBoundingClientRect().height;
      console.log(headerBottom);
      
      
      var cardTop = this.getBoundingClientRect().top;
      console.log(cardTop);
      window.scrollBy(0, 60);
      */
      
      
  });
}


/******************************************************************************/



    // hide all articles
function hideAllArticles()
{
    var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;

    for (var i = 0; i < articleElementsNbr; i++)
    {
        allArticleElements[i].style.display = "none";
    }
}

    // display all articles
function displayAllArticles()
{
    var allArticleElements = document.querySelectorAll(".articleElement");
    var articleElementsNbr = allArticleElements.length;

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
    
    closeNav();
    
}


displayVisibleArticleListCorrectly(".articleElement");




