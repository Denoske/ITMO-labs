import React from 'react';
import Plot from './plot/Plot';
import AttemptForm from './AttemptForm';
import AttemptsTable from './AttemptsTable';
import { Link } from 'react-router-dom';

const MainPage = ({serverPort}) => {
  return(
  <div className='main-page-block'>
    <p>
      <Link className='logout_link' to="/" onClick={sendLogoutRequest}>Выйти</Link>
    </p>
    <div className='form-table-box'>
      <AttemptsTable/>
    <AttemptForm serverPort={serverPort}/>
    </div>
    <Plot serverPort={serverPort}/>
  </div>
  );
};

export default MainPage;

let sendLogoutRequest = () =>{
  //todo
}