if(jQuery){
	var checkAnswers = function(){
		var answerString = "";
		var answers = $(":checked");
		
		// 0個めはこれ；<input type="radio" name="question1" value="b">
		//console.log(answers[0])
			// 1個めはこれ；<input type="radio" name="question1" value="c">
		//console.log(answers[1])
		
		answers.each(function(i) {
			answerString = answerString + answers[i].value;
			//console.log("A: " + answerString);
		});
	
		checkIfCorrect(answerString);
		// console.log("B: " + answerString);
		
		// 正解の求め方
		//console.log((811124566973).toString(16));
	};

	var checkIfCorrect = function(theString){
		// console.log("theString : " + theString);
		if(parseInt(theString, 16) === 811124566973){
			$("body").addClass("correct");
			$("h1").text("大正解！");
			$("canvas").show();
		}
	};
	
	$("#question1").show();
};

if(impress){
  $("#question2").show();
};
if(atom){
  $("#question3").show();
};
if(createjs){
  $("#question4").show();
};
if(me){
  $("#question5").show();
};
if(require){
  $("#question6").show();
};
if($().playground){
  $("#question7").show();
};
if(jaws){
  $("#question8").show();
};
if(enchant){
  $("#question9").show();
};
if(Crafty){
  $("#question10").show();
};
