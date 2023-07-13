var itemBoxes = document.querySelectorAll('.inventory-box');
/*
var len = itemBoxes.length;
for(var i=0; i<len; i++){
	console.log(itemBoxes[i]);
}
*/
/*
[].forEach.call(itemBoxes, function (item, i, array) {
   console.log(item + ": " + i + ": " + array);
});
*/

[].forEach.call(itemBoxes, function(itemBox) {
  itemBox.addEventListener('dragstart', handleDragStart);
  itemBox.addEventListener('dragover', handleDragOver);
  itemBox.addEventListener('drop', handleDrop);
});
var draggingObject;
function handleDragStart(e) {
  draggingObject = this;
  //console.log(draggingObject);
  e.dataTransfer.setData('text/html', this.innerHTML);
  var dragIcon = document.createElement('img');
 	var imageName = this.firstChild.id;
  //console.log(imageName);
  dragIcon.src = imageName + '.png';
  e.dataTransfer.setDragImage(dragIcon, -10, 10);
}
function handleDragOver(e) {
  e.preventDefault(); 
}
function handleDrop(e) {
  e.preventDefault();
  // console.log(draggingObject);
 // console.log(this);
  if (draggingObject != this) {
    var draggingGrandpa = draggingObject.parentElement.parentElement;
    // console.log(draggingGrandpa);
    var draggedToGrandpa = this.parentElement.parentElement;
   // console.log(draggedToGrandpa);
    var draggingObjectId = draggingObject.firstChild.id;
    // console.log(draggingObjectId)
    
    inventoryObject.add(draggedToGrandpa.id, draggingObjectId);
    inventoryObject.remove(draggingGrandpa.id, draggingObjectId);
    // console.log(draggedToGrandpa.id);
    // console.log(draggingGrandpa.id)
    draggingObject.innerHTML = this.innerHTML;
    this.innerHTML = e.dataTransfer.getData('text/html');
    this.classList.remove('empty');
    draggingObject.classList.add('empty');
  }
}
