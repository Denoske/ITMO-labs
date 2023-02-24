import React, {useEffect, useState} from 'react';
import {drawPlot, drawPlotAfterClick, drawPlotWithPoints, updatePlot} from './plotScripts';
import { useSelector, useDispatch } from 'react-redux';
import { addAttempt, selectAttempts } from '../../../slices/AttemptSlice';
import { selectToken } from '../../../slices/tokenSlice';


const Plot = ({serverPort}) => {
  var attempts =  useSelector(selectAttempts);
  const token =  useSelector(selectToken);
  const dispatch = useDispatch();


  useEffect(() => {
    drawPlot(attempts);
  });



  let upd= ()=>{updatePlot(attempts)};
  useEffect(() => {
    const interval = setInterval(() => {
      //updatePlot(attempts);
    }, 4000);
    return () => clearInterval(interval);
  }, []);
  //let upd = (e)=>updatePlot(attempts);
  let addPoint = (e) => {
    let coordinates = drawPlotAfterClick(e);
    if(coordinates !== null){
      console.log(token);
  
      console.log("Attempt entered by user:");
      console.log(coordinates);
  
      tryToSendAddAttemptRequest(serverPort, token, coordinates).then(
      (newAttempt) => {
          console.log("Got this attempt from server:");
          console.log(newAttempt);
          dispatch(addAttempt(newAttempt));
          drawPlotAfterClick(attempts);
          //todo: draw plot and add it to table. (Maybe they both could just subscribe to the state data)
          }
        ).catch(() => {
        //todo: maybe token is expired - need to go to login page
        console.log("Adding attempt finished with error!");
        }
      );
    }else{
      console.log("coordinates out of bounds or user's token is expired!");
    }
  }

  return <div id='plot' className='plot box'  onMouseEnter={upd} onClick={addPoint}/>;
};

export default Plot;

let tryToSendAddAttemptRequest = async (port, token, data) => {
  console.log(port);
  let url = "http://localhost:"+ port +"/attempts";
  console.log("Sending POST request to url: " + url + ". With body: " + JSON.stringify(data));
  const response = await fetch(url, {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
      'Authorization': "Bearer " + token
    },
    mode: 'cors',
    body: JSON.stringify(data),
  });
  return await response.json();
}