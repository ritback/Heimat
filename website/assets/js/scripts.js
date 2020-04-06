

var articleTitlesList = document.getElementsByClassName("articleListTitle");
var i, j;

for (i = 0; i < articleTitlesList.length; i++) {
    articleTitlesList[i].addEventListener("click", function(){
      
      // close other panels
        var otherPanel;
      for(j = 0; j < articleTitlesList.length; j++){
          // remove transition
          otherPanel = articleTitlesList[j].nextElementSibling;
          otherPanel.classList.add("panelNoTransition");
          
          if (articleTitlesList[j] != this){   
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

          var headOffset = document.getElementById("head").getBoundingClientRect().bottom;
          window.scrollBy(0, -headOffset);
      
          
          // add back transition
          panel.classList.remove("panelNoTransition"); 
          panel.style.maxHeight = panel.scrollHeight + "px";
      }
      
  });
}

/******************************************************************************/

var accordionTitleButtons = document.getElementsByClassName("accordionTitleButton");


for (i = 0; i < accordionTitleButtons.length; i++) {
    accordionTitleButtons[i].addEventListener("click", function(){
      
      // close other panels
        var otherPanel;
      for(j = 0; j < accordionTitleButtons.length; j++){
          // remove transition
          otherPanel = accordionTitleButtons[j].nextElementSibling;
          otherPanel.classList.add("panelNoTransition");
          
          if (accordionTitleButtons[j] != this){   
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
      
          var headOffset = document.getElementById("head").getBoundingClientRect().bottom;
          window.scrollBy(0, -headOffset);
      
          
          // add back transition
          panel.classList.remove("panelNoTransition"); 
          
          // resize
          panel.style.maxHeight = panel.scrollHeight + "px";
          
          // resize the parent list;
          let newHeightList = parseInt(panel.parentElement.parentElement.style.maxHeight, 10);
          newHeightList += panel.scrollHeight;
          panel.parentElement.parentElement.style.maxHeight = newHeightList + "px"; 
          
      }
      
  });
}




