import React from 'react';
import AuthorDetailes from './AuthorDetailes';

const Header = ({title}) => {
  return <div className='header'>
  <h1>{title}</h1>
    <img src="duck.png" width="75px" alt="41" />
  <AuthorDetailes/>
  </div>;
};

export default Header;
